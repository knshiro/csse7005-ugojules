package csse4003.frontend;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.SpringLayout;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import csse4003.server.MainDialog;
import csse4003.utils.Message;
import csse4003.utils.PhoneBook;
import csse4003.utils.PhoneBookEntry;
import csse4003.utils.SpringUtil;
import csse4003.utils.Message.Block;
/**
 * 
 * Base skeleton for the ViewContactDialog used on the Server-Side for CSSE4003/7005 A5
 * 
 * You are free to edit this class
 * @author Shin
 *
 */
@SuppressWarnings("serial")
public class ViewContactDialog extends JPanel implements ActionListener  {

	private PhoneBook pb; 


	private JList contactList;
	private DefaultListModel listModel = new DefaultListModel();

	private JLabel contactNameLabel = new JLabel();
	private JLabel contactNumberLabel = new JLabel();
	private JLabel contactEmailLabel = new JLabel();
	private JLabel contactRingLabel = new JLabel();
	private JLabel contactVibLabel = new JLabel();
	private JLabel contactLedLabel = new JLabel();
	private JLabel contactRingOptionLabel = new JLabel();

	private JTextField contactName = new JTextField();
	private JTextField contactNumber = new JTextField();
	private JTextField contactEmail = new JTextField();

	private JComboBox ringBox = new JComboBox();
	private JComboBox ledBox = new JComboBox();
	private JComboBox vibBox = new JComboBox();
	private JComboBox ringOptionBox = new JComboBox();

	private JLabel contactPicture = new JLabel();

	private JButton saveButton = new JButton();
	private JButton cancelButton = new JButton();

	private JButton editButton = new JButton();
	private JButton callButton = new JButton();
	private JButton deleteButton = new JButton();

	public ViewContactDialog() {
		init();
		setEditMode(true);
	}

	public void saveGestures() {
		System.out.println("Saving Gesture");
	}

	public void loadGestures() {
		System.out.println("Loading Gesture");
	}

	private ImageIcon scale(Image src, int w,int h) {
        int type = BufferedImage.TYPE_INT_RGB;
        BufferedImage dst = new BufferedImage(w, h, type);
        Graphics2D g2 = dst.createGraphics();
        g2.drawImage(src, 0, 0, w, h, this);
        g2.dispose();
        return new ImageIcon(dst);
    }

	
	public void init() {

		this.setLayout(new BorderLayout());

		cancelButton.setText("Cancel");
		cancelButton.setActionCommand("CANCEL");

		saveButton.setText("Save");
		saveButton.setVisible(false);
		saveButton.setActionCommand("SAVE");

		editButton.setText("Edit");
		editButton.setActionCommand("EDIT");

		deleteButton.setText("Delete");
		deleteButton.setActionCommand("DELETE");

		callButton.setText("Call");
		callButton.setActionCommand("CALL");


		contactNameLabel.setText("Name: ");
		contactNumberLabel.setText("Number: ");
		contactEmailLabel.setText("Email: ");
		contactVibLabel.setText("Vib Pattern: ");
		contactLedLabel.setText("Led Pattern: ");
		contactRingOptionLabel.setText("Ring Option: ");
		contactRingLabel.setText("Ringtone: ");

		contactPicture.setText("No Picture");
		contactPicture.setHorizontalAlignment(JLabel.CENTER);
		contactPicture.setVerticalTextPosition(JLabel.CENTER);

		cancelButton.addActionListener(this);
		saveButton.addActionListener(this);
		deleteButton.addActionListener(this);
		editButton.addActionListener(this);
		callButton.addActionListener(this);

		contactPicture.setPreferredSize(new Dimension(100, 170));

		JPanel contactButtonContent = new JPanel(new GridLayout(3, 1, 5, 5));
		JPanel listButtonContent = new JPanel(new FlowLayout());
		JPanel centralContent = new JPanel(new SpringLayout());
		JPanel leftContent = new JPanel(new GridLayout(0, 1, 5, 5));
		JPanel rightContent = new JPanel(new GridLayout(0, 1, 5 ,5));

		contactButtonContent.add(callButton);
		contactButtonContent.add(editButton);
		contactButtonContent.add(deleteButton);

		listModel.addElement("New Contact");

		contactList = new JList(listModel);

		JScrollPane listScroller = new JScrollPane(contactList);
		listScroller.setPreferredSize(new Dimension(150, 0));
		listScroller.setAlignmentX(LEFT_ALIGNMENT);

		JPanel listPane = new JPanel();
		listPane.setLayout(new BoxLayout(listPane, BoxLayout.PAGE_AXIS));
		JLabel listLabel = new JLabel("Contacts");
		listLabel.setLabelFor(contactList);
		listPane.add(listLabel);
		listPane.add(Box.createRigidArea(new Dimension(0, 5)));
		listPane.add(listScroller);
		listPane.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

		contactList.setSelectedIndex(0);
		contactList.addListSelectionListener(new ListSelectionListener(){

			public void valueChanged(ListSelectionEvent e) {
				int ind = contactList.getSelectedIndex()-1;
				if(ind<0){
					contactName.setText("");
					contactNumber.setText("");
					contactEmail.setText("");
					ringBox.setSelectedItem("");
					vibBox.setSelectedItem("");
					ledBox.setSelectedItem("");
					ringOptionBox.setSelectedItem("");
					contactPicture.setIcon(new ImageIcon(""));
					setEditMode(true);
				}
				else {
					System.out.println("Currently Selected: " + contactList.getSelectedIndex() + ": " + contactList.getSelectedValue());
					contactName.setText(pb.entries.get(ind).fields[0]);
					contactNumber.setText(pb.entries.get(ind).fields[1]);
					contactEmail.setText(pb.entries.get(ind).fields[2]);
					setSelected(ringBox,pb.entries.get(ind).fields[4]);
					vibBox.setSelectedItem(pb.entries.get(ind).fields[5]);
					ledBox.setSelectedItem(pb.entries.get(ind).fields[6]);
					ringOptionBox.setSelectedIndex(Integer.parseInt(pb.entries.get(ind).fields[7]));
					if (new File(pb.entries.get(ind).fields[3]).exists())
						contactPicture.setIcon(scale(new ImageIcon(pb.entries.get(ind).fields[3]).getImage(),100,170));
					else 
						contactPicture.setIcon(null);
					setEditMode(false);

				}
			}

		});
		
		
		
		contactList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		leftContent.add(listPane);

		centralContent.add(contactNameLabel);
		centralContent.add(contactName);
		centralContent.add(contactNumberLabel);
		centralContent.add(contactNumber);
		centralContent.add(contactEmailLabel);
		centralContent.add(contactEmail);
		centralContent.add(contactRingLabel);
		centralContent.add(ringBox);
		centralContent.add(contactVibLabel);
		centralContent.add(vibBox);
		centralContent.add(contactLedLabel);
		centralContent.add(ledBox);
		centralContent.add(contactRingOptionLabel);
		centralContent.add(ringOptionBox);
		centralContent.add(new JLabel(""));
		centralContent.add(listButtonContent);

		ringOptionBox.addItem("Orchestra");
		ringOptionBox.addItem("Synchronized");

		SpringUtil.makeCompactGrid(centralContent, 
				8, 2,
				5, 5,
				5, 5);

		rightContent.add(contactPicture);
		rightContent.add(contactButtonContent);

		listButtonContent.add(saveButton);
		listButtonContent.add(cancelButton);

		JPanel contactPane = new JPanel();
		contactPane.setLayout(new BoxLayout(contactPane, BoxLayout.PAGE_AXIS));
		contactPane.add(contactPicture);
		listPane.add(Box.createRigidArea(new Dimension(0, 20)));
		contactPane.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

		contactPane.add(contactButtonContent);

		add(leftContent, BorderLayout.WEST);		
		add(centralContent, BorderLayout.CENTER);
		add(contactPane, BorderLayout.EAST);

	}

	public void setEditMode(boolean edit){
		if(edit&&MainDialog.connected){
			saveButton.setVisible(true);
			contactEmail.setEditable(true);
			contactName.setEditable(true);
			contactNumber.setEditable(true);
			ringBox.setEnabled(true);
			ringOptionBox.setEnabled(true);
			ledBox.setEnabled(true);
			vibBox.setEnabled(true);
		}
		else {
			saveButton.setVisible(false);
			contactEmail.setEditable(false);
			contactName.setEditable(false);
			contactNumber.setEditable(false);
			ringBox.setEnabled(false);
			ringOptionBox.setEnabled(false);
			ledBox.setEnabled(false);	
			vibBox.setEnabled(false);
		}
	}

	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("EDIT")) {
			setEditMode(true);

		} else if (e.getActionCommand().equals("SAVE")) {
			if(contactName.getText().equals("")||contactNumber.getText().equals("")){
				JOptionPane.showMessageDialog(this,"You must provide at least a name and phone number");
				return;
			}
			setEditMode(false);
			String[] fields = new String[9];
			fields[0]=contactName.getText();
			fields[1]=contactNumber.getText();
			fields[2]=contactEmail.getText();
			fields[4]=(String)ringBox.getSelectedItem();
			fields[5]=(String)vibBox.getSelectedItem();
			fields[6]=(String)ledBox.getSelectedItem();
			fields[7]=""+ringOptionBox.getSelectedIndex();
			if(contactList.getSelectedIndex()==0){
				fields[3]="";
				fields[8]="0";
				pb.add(new PhoneBookEntry(fields));
				setPhoneBook(pb);
			}
			else {
				fields[3]=pb.entries.get(contactList.getSelectedIndex()-1).fields[3];
				fields[8]=pb.entries.get(contactList.getSelectedIndex()-1).fields[8];
				pb.entries.get(contactList.getSelectedIndex()-1).fields=fields;
			}
			try {
				MainDialog.sendSync(pb);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		} else if (e.getActionCommand().equals("CANCEL")) {
			if(contactList.getSelectedIndex()>0){
				contactList.setSelectedIndex(contactList.getSelectedIndex()-1);
				contactList.setSelectedIndex(contactList.getSelectedIndex()+1);
			}
			else {
				contactList.setSelectedIndex(contactList.getSelectedIndex()+1);
				contactList.setSelectedIndex(contactList.getSelectedIndex()-1);
			}
		} else if (e.getActionCommand().equals("DELETE")) {
			if(contactList.getSelectedIndex()>0){
				if(JOptionPane.showConfirmDialog(null,"Delete "+
						pb.entries.get(contactList.getSelectedIndex()-1).fields[0]+" ?")==JOptionPane.YES_OPTION){
					pb.entries.remove(contactList.getSelectedIndex()-1);
					contactList.setSelectedIndex(contactList.getSelectedIndex()-1);
					try {
						MainDialog.sendSync(pb);
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					setPhoneBook(pb);
				}
			}
		} else if (e.getActionCommand().equals("CALL")) {
			if(contactList.getSelectedIndex()>0){
				try {
					MainDialog.sendCall(contactList.getSelectedIndex()-1);
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		} else {
			System.out.println("actionPerformed: " + e.getActionCommand());
		}
	}

	private void setSelected(JComboBox box, String s){
		for (int i = 0; i < box.getItemCount(); i++) {
			if(((String)box.getItemAt(i)).equals(s))
				box.setSelectedIndex(i);
		}
	}

	public void setPhoneBook(PhoneBook pb){
		this.pb=pb;
		listModel.clear();
		listModel.addElement("New Contact");
		contactList.setSelectedIndex(0);
		for (int i = 0; i < pb.entries.size(); i++) {
			listModel.addElement(pb.entries.get(i).fields[0]);
		}
	}


	public void sync(Message msg){
		setPhoneBook(msg.phonebook);
		ringBox.removeAllItems();
		for(String ring : msg.blocks[Block.RINGTONES.i()]){
			ringBox.addItem(ring);
		}
		vibBox.removeAllItems();
		for(String vib : msg.blocks[Block.VIBS.i()]){
			vibBox.addItem(vib);
		}
		ledBox.removeAllItems();
		for(String led : msg.blocks[Block.LEDS.i()]){
			ledBox.addItem(led);
		}

	}


	/**
	 * Module that handles the creation of the gesture recording dialog
	 */
}
