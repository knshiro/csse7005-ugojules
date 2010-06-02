package csse4003.utils;

public class PhoneBookEntry {
	String contactName;
	String phoneNumber;
	String contactEmail;
	String pictureFilePath;
	String ringtone;
	String vibrationPattern;
	String ledPattern;
	int ringOption;
	int ringOffset;
	public String[] fields;
	
	public PhoneBookEntry(String line){
		fields = line.split("\\|");
	}
	
	public PhoneBookEntry(String[] f){
		fields=f;
	}
	
	public String toString(){
		String res = "";
		for (int i = 0; i < fields.length-1; i++) {
			res+=fields[i]+"|";
		}
		res+=fields[fields.length-1];
		return res;
	}
	
	
	
	
}
