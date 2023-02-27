#include "Message.h"
// Message 

void Message::save(Folder& f) {
	folders.insert(&f);
	f.addMsg(this);
}
void Message::remove(Folder& f) {
	folders.erase(&f);
	f.remMsg(this);
}
void Message::add_to_Folders(const Message& m) {
	for (auto f : m.folders)
		f->addMsg(this);
}
void Message::remove_from_Folders() {
	for (auto f : folders)
		f->remMsg(this);
}
void Message::move_Folders(Message* m)
{
	folders = std::move(m->folders); // uses set move assignment
	
	for (auto f : folders) {
		f->remMsg(m); // remove old message from the folder
		f->addMsg(this); // add this message to that folder
	}
	m->folders.clear();
}
Message::Message(const Message& m) :
	contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}
Message::Message(Message&& m) : contents(std::move(m.contents))
{
	move_Folders(&m);
}
Message& Message::operator=(Message&& rhs)
{
	if (this != &rhs) {						//self - assignment
		remove_from_Folders();		
		contents = std::move(rhs.contents); // move assignment
		move_Folders(&rhs);					// resets folder point to this Message
	}
	return *this;
}
Message& Message::operator=(const Message& rhs) {
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}
Message::~Message() {
	remove_from_Folders();
}
std::ostream& Message::print(std::ostream& os) {
	return 
		os << contents << " appears in : " 
		<< folders.size() << " folders.";
}

// Folder
void Folder::save(Message& m) {
	messages.insert(&m);
	m.addFld(this);
}
void Folder::remove(Message& m) {
	messages.erase(&m);
	m.remFld(this);
}
Folder::Folder(const Folder& f): messages(f.messages)
{
	add_to_Messages(f);
}
Folder& Folder::operator=(const Folder& rhs)
{
	remove_from_Messages();
	messages = rhs.messages;
	add_to_Messages(rhs);
	return *this;

}
Folder::~Folder()
{
	remove_from_Messages();
}
void Folder::add_to_Messages(const Folder& f)
{
	for (auto m : f.messages)
		m->addFld(this);
}
void Folder::remove_from_Messages()
{
	for (auto m : messages)
		m->remFld(this);
}
void Folder::print()
{
	std::cout << "Folder:" << std::endl;
	for (auto m : messages)
		std::cout << "\t" << m->contents << std::endl;
}


void swap(Message& lhs, Message& rhs) {
	// remove pointers
	using std::swap;
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	// swap
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);

	// add pointers
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);

}
