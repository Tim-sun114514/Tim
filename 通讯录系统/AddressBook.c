#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 1000
#define NAME_LEN 50
#define GENDER_LEN 10
#define PHONE_LEN 20
#define EMAIL_LEN 80
#define ADDRESS_LEN 120
#define DATA_FILE "contacts.dat"

typedef struct {
    char name[NAME_LEN];
    char gender[GENDER_LEN];
    int age;
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    char address[ADDRESS_LEN];
} Contact;

typedef struct {
    Contact items[MAX_CONTACTS];
    int count;
} AddressBook;

static void clear_input_buffer(void);
static void read_line(const char *prompt, char *buffer, int size);
static int read_int(const char *prompt, int min, int max);
static void press_enter_to_continue(void);
static void print_menu(void);
static void print_contact_header(void);
static void print_contact(const Contact *contact, int index);
static int find_by_phone(const AddressBook *book, const char *phone);
static int add_contact(AddressBook *book);
static void list_contacts(const AddressBook *book);
static void search_contacts(const AddressBook *book);
static int update_contact(AddressBook *book);
static int delete_contact(AddressBook *book);
static int sort_contacts(AddressBook *book);
static void save_contacts(const AddressBook *book);
static void load_contacts(AddressBook *book);

int main(void) {
    AddressBook book = {0};
    int choice;

    load_contacts(&book);

    while (1) {
        print_menu();
        choice = read_int("Choose an option: ", 0, 7);

        switch (choice) {
            case 1:
                if (add_contact(&book)) {
                    save_contacts(&book);
                }
                break;
            case 2:
                list_contacts(&book);
                break;
            case 3:
                search_contacts(&book);
                break;
            case 4:
                if (update_contact(&book)) {
                    save_contacts(&book);
                }
                break;
            case 5:
                if (delete_contact(&book)) {
                    save_contacts(&book);
                }
                break;
            case 6:
                if (sort_contacts(&book)) {
                    save_contacts(&book);
                }
                break;
            case 7:
                save_contacts(&book);
                break;
            case 0:
                save_contacts(&book);
                puts("Address book closed.");
                return 0;
            default:
                puts("Invalid option. Please try again.");
                break;
        }

        press_enter_to_continue();
    }
}

static void clear_input_buffer(void) {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static void read_line(const char *prompt, char *buffer, int size) {
    size_t len;

    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        clear_input_buffer();
        return;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        clear_input_buffer();
    }
}

static int read_int(const char *prompt, int min, int max) {
    char input[32];
    char *endptr;
    long value;

    while (1) {
        read_line(prompt, input, sizeof(input));
        value = strtol(input, &endptr, 10);

        if (input[0] != '\0' && *endptr == '\0' && value >= min && value <= max) {
            return (int)value;
        }

        printf("Please enter an integer from %d to %d.\n", min, max);
    }
}

static void press_enter_to_continue(void) {
    char input[4];

    puts("\nPress Enter to continue...");
    fgets(input, sizeof(input), stdin);
}

static void print_menu(void) {
    puts("\n========== Address Book Management ==========");
    puts("1. Add contact");
    puts("2. Show all contacts");
    puts("3. Search contacts");
    puts("4. Update contact");
    puts("5. Delete contact");
    puts("6. Sort by name");
    puts("7. Save contacts");
    puts("0. Save and exit");
    puts("=============================================");
}

static void print_contact_header(void) {
    printf("%-5s %-16s %-8s %-5s %-18s %-28s %-30s\n",
           "No.", "Name", "Gender", "Age", "Phone", "Email", "Address");
    puts("---------------------------------------------------------------------------------------------------------");
}

static void print_contact(const Contact *contact, int index) {
    printf("%-5d %-16s %-8s %-5d %-18s %-28s %-30s\n",
           index + 1,
           contact->name,
           contact->gender,
           contact->age,
           contact->phone,
           contact->email,
           contact->address);
}

static int find_by_phone(const AddressBook *book, const char *phone) {
    int i;

    for (i = 0; i < book->count; i++) {
        if (strcmp(book->items[i].phone, phone) == 0) {
            return i;
        }
    }

    return -1;
}

static int add_contact(AddressBook *book) {
    Contact contact;

    if (book->count >= MAX_CONTACTS) {
        puts("The address book is full.");
        return 0;
    }

    puts("\n--- Add Contact ---");
    read_line("Name: ", contact.name, sizeof(contact.name));
    read_line("Gender: ", contact.gender, sizeof(contact.gender));
    contact.age = read_int("Age: ", 0, 150);
    read_line("Phone: ", contact.phone, sizeof(contact.phone));

    if (find_by_phone(book, contact.phone) != -1) {
        puts("This phone number already exists. Add failed.");
        return 0;
    }

    read_line("Email: ", contact.email, sizeof(contact.email));
    read_line("Address: ", contact.address, sizeof(contact.address));

    book->items[book->count++] = contact;
    puts("Contact added successfully.");
    return 1;
}

static void list_contacts(const AddressBook *book) {
    int i;

    puts("\n--- All Contacts ---");
    if (book->count == 0) {
        puts("The address book is empty.");
        return;
    }

    print_contact_header();
    for (i = 0; i < book->count; i++) {
        print_contact(&book->items[i], i);
    }
}

static void search_contacts(const AddressBook *book) {
    char keyword[NAME_LEN];
    int i;
    int found = 0;

    puts("\n--- Search Contacts ---");
    read_line("Enter a name keyword: ", keyword, sizeof(keyword));

    for (i = 0; i < book->count; i++) {
        if (strstr(book->items[i].name, keyword) != NULL) {
            if (!found) {
                print_contact_header();
            }
            print_contact(&book->items[i], i);
            found = 1;
        }
    }

    if (!found) {
        puts("No matching contacts found.");
    }
}

static int update_contact(AddressBook *book) {
    char phone[PHONE_LEN];
    int index;
    Contact updated;

    puts("\n--- Update Contact ---");
    read_line("Enter the phone number to update: ", phone, sizeof(phone));
    index = find_by_phone(book, phone);

    if (index == -1) {
        puts("Contact not found.");
        return 0;
    }

    puts("Current contact:");
    print_contact_header();
    print_contact(&book->items[index], index);

    read_line("New name: ", updated.name, sizeof(updated.name));
    read_line("New gender: ", updated.gender, sizeof(updated.gender));
    updated.age = read_int("New age: ", 0, 150);
    read_line("New phone: ", updated.phone, sizeof(updated.phone));

    if (strcmp(phone, updated.phone) != 0 && find_by_phone(book, updated.phone) != -1) {
        puts("The new phone number already exists. Update failed.");
        return 0;
    }

    read_line("New email: ", updated.email, sizeof(updated.email));
    read_line("New address: ", updated.address, sizeof(updated.address));

    book->items[index] = updated;
    puts("Contact updated successfully.");
    return 1;
}

static int delete_contact(AddressBook *book) {
    char phone[PHONE_LEN];
    int index;
    int i;

    puts("\n--- Delete Contact ---");
    read_line("Enter the phone number to delete: ", phone, sizeof(phone));
    index = find_by_phone(book, phone);

    if (index == -1) {
        puts("Contact not found.");
        return 0;
    }

    for (i = index; i < book->count - 1; i++) {
        book->items[i] = book->items[i + 1];
    }
    book->count--;

    puts("Contact deleted successfully.");
    return 1;
}

static int sort_contacts(AddressBook *book) {
    int i;
    int j;

    for (i = 0; i < book->count - 1; i++) {
        for (j = 0; j < book->count - 1 - i; j++) {
            if (strcmp(book->items[j].name, book->items[j + 1].name) > 0) {
                Contact temp = book->items[j];
                book->items[j] = book->items[j + 1];
                book->items[j + 1] = temp;
            }
        }
    }

    puts("Contacts sorted by name.");
    return 1;
}

static void save_contacts(const AddressBook *book) {
    FILE *file = fopen(DATA_FILE, "wb");

    if (file == NULL) {
        puts("Save failed. Could not open the data file.");
        return;
    }

    fwrite(&book->count, sizeof(book->count), 1, file);
    fwrite(book->items, sizeof(Contact), book->count, file);
    fclose(file);

    puts("Contacts saved.");
}

static void load_contacts(AddressBook *book) {
    FILE *file = fopen(DATA_FILE, "rb");

    if (file == NULL) {
        return;
    }

    if (fread(&book->count, sizeof(book->count), 1, file) != 1 ||
        book->count < 0 ||
        book->count > MAX_CONTACTS) {
        book->count = 0;
        fclose(file);
        puts("Data file is damaged. An empty address book has been created.");
        return;
    }

    if (fread(book->items, sizeof(Contact), book->count, file) != (size_t)book->count) {
        book->count = 0;
        puts("Data file is incomplete. An empty address book has been created.");
    }

    fclose(file);
}
