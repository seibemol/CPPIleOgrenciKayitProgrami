#include <iostream>	//cin ve cout komutlarının kullanılabilmesi için gerekli olan kütüphane.
#include <fstream>	//dosya işlemleri için gerekli olan kütüphane.
#include <string>	//string veri türündeki kodların okunması için gerekli olan kütüphane.
#include <algorithm>	//bilgi üzerinde işlem yapmamıza olanak sağlayan kütüphane.
#include <vector>	//her tür veri tipi ya da nesneyi tutmamız için gerekli olan kütüphane.
#include <cstdlib>	//sayıları metne, metinleri sayıya çevirebilmek ve rastgele sayılar üretebilmek için gerekli kütüphane.
#include <ctime>	//tarih ve zamanı yönetebilmemiz için gerekli olan kütüphane.
#include <set>		//verileri depolamak ve almak için gerekli olan kütüphane.

using namespace std; //eğer cout komutu çokça kullanılacaksa hepsini tanımlamaya yarar.

// Ad ve soyad dosyalarının okunması için fonksiyon ////vector, belirli türdeki ögeleri doğrusal bir düzende depolamayı sağlar. gerektiğinde depolama boyutunu büyür.
vector<string> readFile(string fileName) {
	vector<string> lines;
	string line;
	ifstream file(fileName);
	if (file.is_open()) {
		while (getline(file, line)) {
			lines.push_back(line);
		}
		file.close();
	}
	return lines;
}

// Öğrenci yapısı ////struct, gruplandırılmış değişkenler listesini tanımlar.
struct Student {
	string name;	//adlar için kullanılan değişken
	string surname;	//soyadlar için kullanılan değişken
	int age;		//yaşlar için kullanılan değişken
	int score;		//puanlar için kullanılan değişken
	string answers;	//cevaplar için kullanılan değişken
};

// Öğrenci cevaplarının değerlendirilmesi ////void, veri tipini belirtmediğimiz fonksiyonlar için kullanılır.
void evaluateAnswers(Student& student, string answerKey) {
	student.score = 0;
	for (int i = 0; i < answerKey.size(); i++) {
		if (student.answers[i] == answerKey[i]) {
			student.score += 10;
		}
	}
}

// Öğrenci listesinin ekrana yazdırılması
void printStudents(vector<Student> students) {
	cout << "Öğrenciler:" << endl;
	cout << "Ad\tSoyad\tYaş\tPuan\tCevaplar" << endl;
	for (auto student : students) {
		cout << student.name << "\t" << student.surname << "\t" << student.age << "\t" << student.score << "\t" << student.answers << endl;
	}
}

//// int main(), kaynak kodların çalışmasını sağlayan ana fonksiyondur. Kodların çalıştırılmaya başladığı yerdir.
int main() {

	setlocale(LC_ALL, "TURKISH");

	// Ad ve soyad dosyalarını oku
	vector<string> names = readFile("C:\\Users\\seyma\\Desktop\\Algoritma Proje\\ad.txt");
	vector<string> surnames = readFile("C:\\Users\\seyma\\Desktop\\Algoritma Proje\\soyad.txt");

	// Cevap anahtarını kullanıcıdan al
	cout << "Lütfen cevap anahtarını girin (10 haneli): ";
	string answerKey;	////cevap anahtarını girmek için kullanılan değişken
	cin >> answerKey;

	// Öğrenci sayısını kullanıcıdan al
	cout << "Kaç öğrenci oluşturulsun? (0-2500): ";
	int studentCount;	////öğrenci sayısını girmek için kullanılan değişken
	cin >> studentCount;
	// Öğrencileri oluştur ve cevaplarını değerlendir
	vector<Student> students;
	set<pair<string, string>> usedNames;
	srand(time(0));
	for (int i = 0; i < studentCount; i++) {
		Student student;
		do {
			student.name = names[rand() % names.size()];
			student.surname = surnames[rand() % surnames.size()];
		} while (usedNames.count({ student.name, student.surname }) > 0);
		usedNames.insert({ student.name, student.surname });
		student.age = 18 + rand() % 43;
		for (int j = 0; j < 10; j++) {
			student.answers += rand() % 2 == 0 ? 'D' : 'Y';
		}
		evaluateAnswers(student, answerKey);
		students.push_back(student);
	}

	// Öğrencileri ekrana yazdır
	printStudents(students);

	// Sıralama tipini kullanıcıdan al
	cout << "Sıralama tipini seçin (1: Ad, 2: Soyad, 3: Yaş, 4: Puan): ";
	int sortType;	////sıralama şekli değişkeni
	cin >> sortType;

	// Öğrencileri sırala
	if (sortType == 1) {
		sort(students.begin(), students.end(), [](const Student& s1, const Student& s2) {
			return s1.name < s2.name;
		});
	}
	else if (sortType == 2) {
		sort(students.begin(), students.end(), [](const Student& s1, const Student& s2) {
			return s1.surname < s2.surname;
		});
	}
	else if (sortType == 3) {
		sort(students.begin(), students.end(), [](const Student& s1, const Student& s2) {
			return s1.age < s2.age;
		});
	}
	else if (sortType == 4) {
		sort(students.begin(), students.end(), [](const Student& s1, const Student& s2) {
			return s1.score > s2.score;
		});
	}

	// Öğrencileri sıralanmış haliyle ekrana yazdır
	printStudents(students);

	return 0;
}