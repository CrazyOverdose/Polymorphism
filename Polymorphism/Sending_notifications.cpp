#include <iostream>
#include <string>


using std::string;
using std::cout;
using std::endl;

void SendSms(const string& number, const string& message) {
	std::cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
	std::cout << "Send '" << message << "' to e-mail " << email << endl;
}


class  INotifier {
public:
	virtual void Notify(const std::string& message) = 0;
};


class SmsNotifier : public INotifier {

public:
		SmsNotifier(const std::string& this_number) : number(this_number) {}

		void Notify(const std::string& message) override {
			SendSms(number, message);
		}

private:
	const string number;
};

class EmailNotifier : public INotifier {

public:
	EmailNotifier(const std::string& this_email) : email(this_email) {}

	void Notify(const std::string& message) override {
		SendEmail(email, message);
	}
private:
	const string email;
};

void Notify(INotifier& notifier, const string& message) {
	notifier.Notify(message);
}

//int main() {
//	SmsNotifier sms{ "+7-495-777-77-77" };
//	EmailNotifier email{ "na-derevnyu@dedushke.ru" };
//
//	Notify(sms, "I have White belt in C++");
//	Notify(email, "And want a Yellow one");
//	return 0;
//}