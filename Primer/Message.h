#pragma once
#include <string>
#include <iostream>
#include <set>


class Folder;
class Message {
	friend class Folder;
	friend void swap(Message&, Message&);
public:
	explicit Message(const std::string& str = "") :
		contents(str) {}
	Message(const Message&);
	Message(Message&&);
	Message& operator=(Message&& rhs);
	Message& operator=(const Message&);
	~Message();

	void save(Folder&);
	void remove(Folder&);

	std::ostream& print(std::ostream&);

private:
	std::string contents;
	std::set<Folder*> folders;
	void add_to_Folders(const Message&);
	void remove_from_Folders();
	// not no_exception - inserion can throw error
	void move_Folders(Message* m);

	void addFld(Folder* f) { folders.insert(f);}
	void remFld(Folder* f) { folders.erase(f); }
};
class Folder {
	friend class Message;
	friend void swap(Message&, Message&);
public:
	Folder() = default;
	Folder(const Folder&);
	Folder& operator=(const Folder&);
	~Folder();

	void save(Message&);
	void remove(Message&);
	
	void print();

private:
	std::set<Message*> messages;

	void add_to_Messages(const Folder&);
	void remove_from_Messages();

	void addMsg(Message* msg) { messages.insert(msg); }
	void remMsg(Message* msg) { messages.erase(msg); }
};
void swap(Message&, Message&);