package csse4003.utils;

import java.util.ArrayList;

public class PhoneBook {

	public ArrayList<PhoneBookEntry> entries;
	public PhoneBook(ArrayList<String> list) {
		entries=new ArrayList<PhoneBookEntry>();
		for(String entry : list){
			entries.add(new PhoneBookEntry(entry));
		}
	}
	
	public void add(PhoneBookEntry e){
		for (int i = 0; i < entries.size(); i++) {
			if(entries.get(i).fields[0].compareToIgnoreCase(e.fields[0])>0){
				entries.add(i, e);
				return;
			}
		}
		entries.add(e);
	}
	
	public String toString(){
		String res="";
		for (int i = 0; i < entries.size(); i++) {
			res+=entries.get(i)+"\n";
		}
		
		return res;
	}

}

