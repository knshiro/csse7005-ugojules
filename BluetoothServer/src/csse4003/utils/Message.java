package csse4003.utils;

import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.TreeMap;

import csse4003.server.MainDialog;

public class Message {
	static boolean firstTime = true;

	/* Network Protocol opcode enumerators */
	static public enum MessageType {
		/* Insert your Opcodes here */
		SYNC(0),CALL(1);

		/* Integer value for the opcode */
		private int _value;

		/* Constructor for opcode enum with integer value */
		MessageType(int value) {
			_value = value;
		}

		/* Returns the integer value for the opcode  */
		public int value() {
			return _value;
		}

		private static TreeMap<Integer, MessageType> _map;
		static {
			_map = new TreeMap<Integer, MessageType>();
			for (MessageType num: MessageType.values()) {
				_map.put(new Integer(num.value()), num);
			}
		}

		public static MessageType lookup(int value) {
			return _map.get(new Integer(value));
		}
	}

	static public enum Block {
		PHONEBOOK(0,"phonebook"),RINGTONES(1,"ringtones"),VIBS(2,"vibs"),LEDS(3,"leds"),IMAGES(4,"images");
		private int _i;
		private String name;
		Block(int value,String name) {
			_i = value;
			this.name=name;
		}
		public int i() {
			return _i;
		}
	}

	public int seqNbr;
	public MessageType type;

	public ArrayList<String>[] blocks;
	public String[] blockNames = {"phonebook","ringtones","vibs","leds","images"};
	public PhoneBook phonebook;
	public byte[] buffer;
	
	public Message(int ind){
		String msg = "1\n"+MessageType.CALL.value()+"\n"+ind+"\n";
		System.out.println(msg);
		buffer=msg.getBytes();
	}
	
	/**
	 * to send sync
	 * @param pb
	 */
	public Message(PhoneBook pb){
		phonebook=pb;
		String msg = "1\n"+MessageType.SYNC.value()+"\nphonebook\n"+phonebook+"/phonebook\n";
		System.out.println(msg);
		buffer=msg.getBytes();
	}
	
	
	
	/**
	 * constructor to parse a message received
	 * @param byteArray
	 * @throws NumberFormatException
	 * @throws IOException
	 */
	public Message(ByteArrayOutputStream byteArray) throws NumberFormatException, IOException {
		buffer = byteArray.toByteArray();
		String msg = new String(buffer);

		String[] lines = msg.split("\n");
		System.out.println("Message received, "+lines.length+" lines");
		this.seqNbr = Integer.parseInt(lines[0]);
		this.type = MessageType.lookup(Integer.parseInt(lines[1]));

		System.out.println("/*** START ** "+type+" *** "+seqNbr+" *****\\");

		switch(type){
		case SYNC:
			blocks=new ArrayList[blockNames.length];
			int offset = 3;
			for (int i = 0; i < blocks.length; i++) {
				offset+=readBlock(i,lines,offset)+2;
				printBlock(i);
			}
			// if first message received, write images in files
			if(firstTime){
				int byteOffset = locateDataStart(lines, offset);
				for (int i = 0; i < blocks[Block.IMAGES.i()].size()/2; i++) {
					FileOutputStream fos = new FileOutputStream(blocks[Block.IMAGES.i()].get(2*i));
					fos.write(buffer,byteOffset, Integer.parseInt(blocks[Block.IMAGES.i()].get(2*i+1)));
					byteOffset+=Integer.parseInt(blocks[Block.IMAGES.i()].get(2*i+1));
				}
				firstTime=false;
			}
			break;
		default:
			System.out.println("ERROR invalid message type");
			break;
		}
		System.out.println("\\*** END ** "+type+" *** "+seqNbr+" *****/");

		phonebook=new PhoneBook(blocks[Block.PHONEBOOK.i()]);
	}


	private int readBlock(int block, String[] lines, int start){
		int i = start;
		blocks[block]=new ArrayList<String>();
		while(!lines[i].equals("/"+blockNames[block])){
			blocks[block].add(lines[i]);
			i++;
		}
		return blocks[block].size();
	}

	private void printBlock(int block){
		System.out.println("|* "+blockNames[block].toUpperCase()+":");
		for (int i = 0; i < blocks[block].size(); i++) {
			System.out.println("|* \t"+blocks[block].get(i));
		}
	}

	public ArrayList<String> getBlock(Block b){
		return blocks[b.i()];
	}

	private int locateDataStart(String[] lines, int lineOffset){
		int offset=0;
		for (int i = 0; i < lineOffset-1; i++) {
			offset+=lines[i].length()+1;
		}
		return offset;
	}

	public static void main(String[] args) throws IOException{
		String msg = "3\n0\nphonebook\ntoto\nlulu\nbibi\n/phonebook\nringtones\nvive le vent\n/ringtones\n" +
		"vibs\ngros god\npetit god\n/vibs\nleds\n/leds\nimages\npere noel\n2\nchat\n3\n/images\naabbb";
		ByteArrayOutputStream array = new ByteArrayOutputStream();
		array.write(msg.getBytes());
		new Message(array);


	}


}
