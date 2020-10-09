# Задание 1. Отправка уведомлений

В этой задаче вам нужно разработать классы SmsNotifier и EmailNotifier, отправляющие уведомления в виде SMS и e-mail соответственно, а также абстрактный базовый класс для них.

Вам даны функции SendSms и SendEmail, которые моделируют отправку SMS и e-mail.
```
void SendSms(const string& number, const string& message);
void SendEmail(const string& email, const string& message);
```

Разработайте:

1. Абстрактный базовый класс INotifier, у которого будет один чисто виртуальный метод void Notify(const string& message).

2. Класс SmsNotifier, который:

+ является потомком класса INotifier;
+ в конструкторе принимает один параметр типа string — номер телефона;
+ переопределяет метод Notify и вызывает из него функцию SendSms.

3. Класс EmailNotifier, который;

+ является потомком класса INotifier;
+ в конструкторе принимает один параметр типа string — адрес электронной почты;
+ переопределяет метод Notify и вызывает из него функцию SendEmail.

# Задание 2. Набор фигур
Вам дана функция main, которая считывает из стандартного ввода команды по работе с набором геометрических фигур:

```
int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
```

Как видно из кода, есть два вида команд:

+ ADD — добавить фигуру в набор;
+ PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.

Программа поддерживает три вида фигур: прямоугольник, треугольник и круг. Их добавление описывается так:

+ ADD RECT width height — добавить прямоугольник с размерами width и height (например, ADD RECT 2 3).
+ ADD TRIANGLE a b c — добавить треугольник со сторонами a, b и c (например, ADD TRIANGLE 3 4 5).
+ ADD CIRCLE r — добавить круг радиуса r (например, ADD CIRCLE 5).

Не меняя функцию main, реализуйте недостающие функции и классы:

+ базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
+ классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
+ функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.

Гарантируется, что размеры всех фигур — это натуральные числа не больше 1000. В качестве значения PI используйте 3,14.

Как будет тестироваться ваш код
В рамках тестирования вашего кода будет два этапа.

На первом этапе будет проверена корректность работы функции CreateFigure: функция возвращает корректный объект, созданный с помощью make_shared<Rect>; если во входной поток функции передана команда на создание прямоугольника (RECT width height); корректный объект, созданный с помощью make_shared<Circle>, если во входной поток функции передана команда на создание круга (CIRCLE r), и т. д. При этом гарантируется, что все команды на создание объектов во входном наборе тестов имеют корректный формат без дополнительных пробелов в начале и конце команды.

На втором этапе автоматическая проверяющая система заменит в вашей программе функцию main на main из условия задачи, скомпилирует получившийся файл и прогонит на наборе тестов, проверив таким образом корректность вашего решения на исходной функции main. При этом гарантируется, что все команды ADD в тестах также корректны.

# Задание 3. Грамотно рефакторим код

В данном задании вам предстоит изменить код таким образом, чтобы он соответствовал изложенным в курсе принципам.
Конечные цели рефакторинга:

+ упростить дальнейшую поддержку кода;
+ уменьшить сложность кода;
+ упростить добавление новых абстракций в программу.

Задание будет оцениваться по следующим критериям:

+ эффективность выполнения кода;
+ задублированность кода;
+ эффективность использования приёмов рефакторинга кода, показанных в лекциях.
+ Кроме того, присылаемый вами код должен компилироваться.

Код:
```
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Student {
public:

    Student(string name, string favouriteSong) {
        Name = name;
        FavouriteSong = favouriteSong;
    }

    void Learn() {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(string destination) {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string Name;
    string FavouriteSong;
};


class Teacher {
public:

    Teacher(string name, string subject) {
        Name = name;
        Subject = subject;
    }

    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

    void Walk(string destination) {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
    string Subject;
};


class Policeman {
public:
    Policeman(string name) {
        Name = name;
    }

    void Check(Teacher t) {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(Student s) {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(Policeman p) {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(string destination) {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
};


void VisitPlaces(Teacher t, vector<string> places) {
    for (auto p : places) {
        t.Walk(p);
    }
}

void VisitPlaces(Student s, vector<string> places) {
    for (auto p : places) {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman pol, vector<string> places) {
    for (auto p : places) {
        pol.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
```
