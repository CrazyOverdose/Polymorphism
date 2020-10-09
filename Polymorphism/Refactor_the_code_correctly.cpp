#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

class People {
public:

	People (const string& name) : Name(name){}
	virtual void Walk(const string& destination) = 0;
	virtual void Check(const People& a) = 0;
	string return_Name() const { return Name; }

protected:
	const string Name;
};

class Student : public People {
public:

	Student(const string& name, const string& favouriteSong) : People(name), FavouriteSong(favouriteSong) {}

	void Learn() {
		cout << "Student: " << Name << " learns" << endl;
	}

	void Walk(const string& destination) override{
		cout << "Student: " << Name << " walks to: " << destination << endl;
		SingSong();
	}
	void SingSong() {
		cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
	}

	void Check(const People& s) override{
		cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.return_Name() << endl;
	}

public:
	const string FavouriteSong;
};


class Teacher : public People {
public:

	Teacher(const string& name, const string& subject) : People(name), Subject (subject){}

	void Teach() {
		cout << "Teacher: " << Name << " teaches: " << Subject << endl;
	}
	void Check(const People& t) override {
		cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.return_Name() << endl;
	}

	void Walk(const string& destination) override {
		cout << "Teacher: " << Name << " walks to: " << destination << endl;
	}


public:
	const string Subject;
};


class Policeman : public People {
public:
	Policeman(const string& name) : People(name) {}

	void Check(const People& p) override {
		cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.return_Name() << endl;
	}

	void Walk(const string& destination) {
		cout << "Policeman: " << Name << " walks to: " << destination << endl;
	}
};

void VisitPlaces(People& pol, const vector<string>& places) {
	for (const auto& p : places) {
		pol.Walk(p);
	}
}

//int main() {
//	Teacher t("Jim", "Math");
//	Student s("Ann", "We will rock you");
//	Policeman p("Bob");
//
//	VisitPlaces(t, { "Moscow", "London" });
//	p.Check(s);
//	VisitPlaces(s, { "Moscow", "London" });
//	return 0;
//}