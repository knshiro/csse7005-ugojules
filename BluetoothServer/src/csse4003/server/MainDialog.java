package csse4003.server;

import java.awt.AWTException;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.Time;
import java.util.TreeMap;

import javax.bluetooth.DiscoveryAgent;
import javax.bluetooth.LocalDevice;
import javax.bluetooth.ServiceRecord;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;
import javax.microedition.io.StreamConnectionNotifier;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.plaf.SliderUI;

import csse4003.frontend.ViewContactDialog;
import csse4003.utils.Message;
import csse4003.utils.PhoneBook;

/**
 * Main dialog class for the Assignment 5
 * 
 * You are free to analyse and modify this class to your liking
 * 
 * @author Shin
 *
 */
@SuppressWarnings("serial")
public class MainDialog extends JPanel {

	static public ViewContactDialog vcd;

	/* Finite State Machine enumerator */
	static protected enum State {
		/* Insert your States here */
		INIT
	}

	/* Finite State Machine state variable initialised */
	static protected State state = State.INIT;

	/* Connection and readings flags */
	static protected boolean takeReading = false;
	static public boolean connected = false;

	/* Global pixel dimensions of host screen */
	static final Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();

	/* Bluetooth service and I/O streams */
	static StreamConnectionNotifier service;
	static protected OutputStream os;
	static protected InputStream is;

	/* User interface variable declrations */
	static protected JLabel titleLabel, channelLabel, messageLabel;
	static protected JMenu fileMenu;
	static protected JMenuBar menuBar;

	/**
	 * Constructor that does nothing for now
	 */
	public MainDialog() {

	}

	public static void sendSync(PhoneBook pb) throws IOException{
		if(connected){
			Message m =new Message(pb);
			os.write(m.buffer);
		}
	}

	public static void sendCall(int ind) throws IOException{
		if(connected){
			Message m =new Message(ind);
			os.write(m.buffer);
		}
	}

	/**
	 * Create the GUI and display it
	 */
	private static void createAndShowGUI() {

		/* Create and setup the user interface dialog */
		JFrame frame = new JFrame("Assignment 5 Server");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(new Dimension(800,400));
		frame.setResizable(false);
		frame.setLocation(dim.width/2-380/2, dim.height/2-300/2);

		menuBar = new JMenuBar();
		fileMenu = new JMenu();

		fileMenu.setText("File");

		JMenuItem exitItem = new JMenuItem();

		exitItem.setText("Exit");
		exitItem.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(ActionEvent e) {
				exit_performed(e);
			}
		});

		fileMenu.add(exitItem);	
		menuBar.add(fileMenu);


		/* Setup the title label */
		titleLabel = new JLabel();
		titleLabel.setHorizontalAlignment(JLabel.CENTER);
		titleLabel.setText("Assignment 5 Server");
		titleLabel.setFont(new Font("Book Antiqua", Font.BOLD, 16));
		titleLabel.setForeground(new Color(223,96,2));

		/* Setup the channel and connection message labels */
		channelLabel = new JLabel("SERVER CHANNEL: 1", JLabel.CENTER);
		messageLabel = new JLabel("[No device connected]", JLabel.CENTER);
		messageLabel.setForeground(Color.RED);

		JPanel upperContent = new JPanel(new GridLayout(0, 1, 0, 0));
		JPanel mainContent = new JPanel(new BorderLayout(3, 3));
		JPanel centreContent = new JPanel(new GridLayout(0, 2, 2, 2));

		upperContent.add(titleLabel);
		upperContent.add(channelLabel);
		upperContent.add(messageLabel);

		mainContent.add(upperContent, BorderLayout.NORTH);
		mainContent.add(centreContent, BorderLayout.SOUTH);
		vcd = new ViewContactDialog();
		mainContent.add(vcd, BorderLayout.CENTER);
		//		mainContent.add(lowerContent, BorderLayout.SOUTH);

		frame.setJMenuBar(menuBar);
		frame.setContentPane(mainContent);
		frame.setVisible(true);

		frame.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent evt) {
				exit_performed(null);
			}
		});

	}

	/**
	 * Sets the dialog status label to msg with text color col
	 * 
	 * @param msg
	 * @param col
	 */
	private static void setMessageLabel(String msg, Color col ) {
		messageLabel.setText("[" + msg + "]");
		messageLabel.setForeground(col);
	}

	/**
	 * Notifies a connected client and closes the application
	 * 
	 * @param e
	 */
	public static void exit_performed(ActionEvent e)
	{
		/*try {
			service.close();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}*/
		System.exit(0);
	}


	/**
	 * Waits for and establishes a Bluetooth socket connection
	 * 
	 * @throws IOException
	 */
	public static void waitForConnection() throws IOException {
		/* Blocking call to accept external client connections */
		StreamConnection conn = (StreamConnection) service.acceptAndOpen();

		/* Setup the socket I/O streams */
		os = conn.openOutputStream();
		is = conn.openInputStream();

		/* Set connection flag to true */
		connected = true;
	}

	/**
	 * Main function 
	 * 
	 * @param args
	 * @throws InterruptedException 
	 * @throws IOException
	 * @throws AWTException
	 */
	public static void main(String[] args) throws InterruptedException {
		boolean testing = false;
		try {
			UIManager.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
		} catch (ClassNotFoundException e3) {
			// TODO Auto-generated catch block
			e3.printStackTrace();
		} catch (InstantiationException e3) {
			// TODO Auto-generated catch block
			e3.printStackTrace();
		} catch (IllegalAccessException e3) {
			// TODO Auto-generated catch block
			e3.printStackTrace();
		} catch (UnsupportedLookAndFeelException e3) {
			// TODO Auto-generated catch block
			e3.printStackTrace();
		}
		/* Create and showing the application GUI */
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				createAndShowGUI();
			}
		});
		Thread.sleep(200);
		if(!testing){

			/* Grab the local Bluetooth device and set it to discoverable */
			LocalDevice local;
			try {
				local = LocalDevice.getLocalDevice();
				local.setDiscoverable(DiscoveryAgent.GIAC);

			} catch (Exception e1) {
				e1.printStackTrace();
				exit_performed(null);
				return;
			}

			/* Declare the Bluetooth RFCOMM URL */
			String url = "btspp://localhost:" + "11111111111111111111111111111123" + 
			";authenticate=false;encrypt=false;name=RFCOMM Server";

			/* Create the Bluetooth service on the next available channel */
			try {
				service = (StreamConnectionNotifier) Connector.open( url );
			} catch (IOException e2) {
				// TODO Auto-generated catch block
				e2.printStackTrace();
				exit_performed(null);
			}

			/* Get the record of the broadcasted service */
			ServiceRecord sr = local.getRecord(service);
			String connURL = sr.getConnectionURL(1, false);

			System.out.println(connURL);
			/* Extract the connection channel number */
			String[] tempStr = connURL.split(";");
			String[] tempStr2 = tempStr[0].split(":");
			String connChannel = tempStr2[2];

			/* Debug prints to confirm BlueCove stack connection */
			System.out.println("Connection URL: " + sr.getConnectionURL(1, false));
			channelLabel.setText("SERVER CHANNEL: " + connChannel);

			/* Block and wait for an external Neo Phone Mouse connection */
			try {
				waitForConnection();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
				exit_performed(null);
			}
			connected=true;
			/* Update the GUI status message to 'Detected' mode */
			setMessageLabel("Detected", new Color(128,128,0));
		}
		/* Server listens forever to any incoming packets from the client */
		final int bufferSize = 65536;
		byte buffer[] = new byte[bufferSize];
		int bytes_read;
		while(true) 
		{
			try {
				System.out.println("Waiting for message");

				ByteArrayOutputStream byteArray = new ByteArrayOutputStream();
				if(!testing){
					do {
						bytes_read = is.read(buffer);
						if(bytes_read != -1){
							System.out.println("received a message, size "+bytes_read);
							byteArray.write(buffer,0,bytes_read);
						}
						Thread.sleep(100);
					} while (is.available()>0);
					if(byteArray.size()==0){
						JOptionPane.showMessageDialog(null,"Client disconnected");
						exit_performed(null);
					}
				}
				else {
					Thread.sleep(3000);
					String msg = "3\n0\nphonebook\ntoto|123|a|DavidBeckham.jpg|musique nulle|petit god|e|f\nlulu|234|b|b|vive le vent|b|b|b\n" +
					"bibi|345|c|c|c|c|c|c\n/phonebook\nringtones\nmusique nulle\nvive le vent\n/ringtones\n" +
					"vibs\ngros god\npetit god\n/vibs\nleds\n/leds\nimages\npere noel\n2\nchat\n3\n/images\naabbb";

					byteArray.write(msg.getBytes());
				}
				/* Extract received text */
				Message received = new Message(byteArray);

				switch(received.type){
				case SYNC:
					vcd.sync(received);
					if(testing)Thread.sleep(100000);

					break;
				}
			}
			catch ( Exception e ) {
				JOptionPane.showMessageDialog(null,"Client disconnected");
				exit_performed(null);

			}
		}
	}

}
