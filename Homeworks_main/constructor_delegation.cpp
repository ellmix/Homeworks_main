#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Contact {
private:
    char* fullName;
    char* homePhone;
    char* workPhone;
    char* mobilePhone;
    char* additionalInfo;

public:
    //Делегирование конструкторов 
    Contact(const char* name, const char* home, const char* work, const char* mobile, const char* info)
        : Contact() {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);

        homePhone = new char[strlen(home) + 1];
        strcpy(homePhone, home);

        workPhone = new char[strlen(work) + 1];
        strcpy(workPhone, work);

        mobilePhone = new char[strlen(mobile) + 1];
        strcpy(mobilePhone, mobile);

        additionalInfo = new char[strlen(info) + 1];
        strcpy(additionalInfo, info);
    }

    Contact()
        : fullName(nullptr), homePhone(nullptr), workPhone(nullptr), mobilePhone(nullptr), additionalInfo(nullptr) {
    }

    ~Contact() {
        delete[] fullName;
        delete[] homePhone;
        delete[] workPhone;
        delete[] mobilePhone;
        delete[] additionalInfo;
    }

    //const char* getFullName() const { return fullName; }
    //const char* getHomePhone() const { return homePhone; }
    //const char* getWorkPhone() const { return workPhone; }
    //const char* getMobilePhone() const { return mobilePhone; }
    //const char* getAdditionalInfo() const { return additionalInfo; }

    void displayContact() {
        cout << "Имя: " << fullName << endl;
        cout << "Домашний телефон: " << homePhone << endl;
        cout << "Рабочий телефон: " << workPhone << endl;
        cout << "Мобильный телефон: " << mobilePhone << endl;
        cout << "Дополнительная информация: " << additionalInfo << endl;
    }
};

class PhoneBook {
private:
    Contact** contacts;
    int size;
    int capacity;

public:
    PhoneBook(int initialCapacity = 10) : size(0), capacity(initialCapacity) {
        contacts = new Contact * [capacity];
    }

    ~PhoneBook() {
        for (int i = 0; i < size; i++) {
            delete contacts[i];
        }
        delete[] contacts;
    }

    void addContact(const char* name, const char* home, const char* work, const char* mobile, const char* info) {
        if (size == capacity) {
            capacity *= 2;
            Contact** newContacts = new Contact * [capacity];
            for (int i = 0; i < size; i++) {
                newContacts[i] = contacts[i];
            }
            delete[] contacts;
            contacts = newContacts;
        }
        contacts[size++] = new Contact(name, home, work, mobile, info);
    }

    void displayContacts() {
        for (int i = 0; i < size; i++) {
            cout << "\nКонтакт #" << i + 1 << endl;
            contacts[i]->displayContact();
            cout << endl;
        }
    }

    void removeContact(int index) {
        if (index >= 0 && index < size) {
            delete contacts[index];
            for (int i = index; i < size - 1; i++) {
                contacts[i] = contacts[i + 1];
            }
            size--;
        }
    }
};

int main() {
    setlocale(LC_ALL, "");
    PhoneBook phoneBook;

    while (true) {
        cout << "1. Добавить контакт" << endl;
        cout << "2. Вывести все контакты" << endl;
        cout << "3. Удалить контакт" << endl;
        cout << "4. Выход" << endl;
        cout << "Выберите действие: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            char name[100], home[100], work[100], mobile[100], info[200];
            cout << "Введите имя: ";
            cin.getline(name, sizeof(name));

            cout << "Введите домашний телефон: ";
            cin.getline(home, sizeof(home));

            cout << "Введите рабочий телефон: ";
            cin.getline(work, sizeof(work));

            cout << "Введите мобильный телефон: ";
            cin.getline(mobile, sizeof(mobile));

            cout << "Введите дополнительную информацию: ";
            cin.getline(info, sizeof(info));

            phoneBook.addContact(name, home, work, mobile, info);
            cout << "Контакт добавлен.\n-----------\n" << endl;
            break;
        }
        case 2:
            phoneBook.displayContacts();
            break;
        case 3: {
            int index;
            cout << "Введите номер контакта для удаления: ";
            cin >> index;
            phoneBook.removeContact(index - 1);
            cout << "Контакт удален.\n-----------\n" << endl;
            break;
        }
        case 4:
            return 0;
        default:
            cout << "Неправильный выбор. Попробуйте снова.\n-----------\n" << endl;
        }
    }

    return 0;
}