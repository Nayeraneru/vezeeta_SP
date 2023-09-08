#include<iostream>
#include <string>
#include <conio.h>
using namespace std;

const int max_doctors = 500;
const int max_patients = 500;
const int max_appointments = 5000;
const int max_available_times = 5000;
struct Doctor;
struct Patient;
struct Appointment {
    Doctor* doctor;
    Patient* patient;
    string date;
    string time;
};

struct Account {
    string username;
    string email;
    string password;
    string confirmPassword;
};

struct Doctor {
    string doc_name;
    Account acc;
    string available_times[max_available_times];
    int num_avaliable_time = 0;

};

struct Patient {
    string pnt_name;
    Account acc;
    int age = 0;
    Appointment* appointments[5000]; // array of pointers
    int num_appointments = 0;
};

Doctor doctors[max_doctors];
Patient patients[max_patients];
Appointment appointments[max_appointments];
int num_doctors = 0;
int num_patients = 0;
int num_avaliable_times = 0;
int num_appointments = 0;

//////////////////////////////////////////// functions used /////////////////////////////////////////////////// 


void register_doctor(Doctor doctors[], int& num_doctors);
void register_patient(Patient patients[], int& num_patients);
bool doctor_login(Doctor doctors[], int num_doctors);
bool patient_login(Patient patients[], int num_patients);
void find_doc(Patient* patient);
void edit_appointment(Patient* patient);
void edit_doctor_info(Doctor* doctor);
void edit_patient_info(Patient* patient);
void add_available_time(Doctor* doctor, int& num_available_times);
void remove_available_time(Doctor* doctor);
void book_appointment(Patient* patient);
void delete_appointment(Patient* patient);
void clear_appointment_history(Patient* patient);
void forget_doc_password(Doctor doctors[], int num_doctors);
void forget_pnt_password(Patient patient[], int num_patients);
void view_patients_with_appointments(Doctor* doctor, Appointment* appointments, int num_appointments);
void view_appointments(Patient* patient);
void edit_available_time(Doctor* doctor, int& num_available_times);
void patient_menu(Patient* patient, Doctor** doctors, int numDoctors, int numAppointments, Appointment** appointments);
void doctor_menu(Doctor* doctor, Appointment* appointments, int num_appointments, int& num_available_times);
void main_menu();

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {


    main_menu();


    return 0;

}
void main_menu()
{
    char choice;
    do {
        cout << "*************************" << endl;
        cout << "Welcome to Vezeeta!" << endl;
        cout << "1. Register as doctor" << endl;
        cout << "2. Register as patient" << endl;
        cout << "3. Log in for doctor" << endl;
        cout << "4. Log in for patient" << endl;
        cout << "5. forget doctor password " << endl;
        cout << "6. forget patient password " << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case '1':

            register_doctor(doctors, num_doctors);
            break;
        case '2':
            register_patient(patients, num_patients);
            break;
        case '3':
            if (doctor_login(doctors, num_doctors))
            {
                doctor_menu(&doctors[0], appointments, num_appointments, num_avaliable_times);
            }
            break;
        case '4':
            if (patient_login(patients, num_patients)) {
                cout << "Patient login successful!" << endl;
                Appointment* appointments = new Appointment;
                Appointment** doublePtr = &appointments;

                Doctor* doctors = new Doctor; // Allocate memory for doctors
                Doctor** doublePtrr = &doctors; // Assign doublePtrr to address of doctors

                patient_menu(&patients[0], doublePtrr, num_doctors, num_appointments, doublePtr);
            }
            break;
        case '5':
            forget_doc_password(doctors, num_doctors);
        case '6':
            forget_pnt_password(patients, num_patients);
        case '7':
            cout << "Exiting Vezeeta" << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (choice != '7');

}
void patient_menu(Patient* patient, Doctor** doctors, int numDoctors, int numAppointments, Appointment** appointments) {
    char choice;
    do {
        cout << "*********************************" << endl;
        cout << "Welcome " << patient->pnt_name << " to Vezeeta!" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Find doctors" << endl;
        cout << "2. Display doctors available to book with" << endl;
        cout << "3. View appointments" << endl;
        cout << "4. Edit appointments" << endl;
        cout << "5. Delete appointments" << endl;
        cout << "6. Clear appointment history" << endl;
        cout << "7. Edit basic info (username/password/age)" << endl;
        cout << "8. Log out" << endl;

        std::cin >> choice;
        switch (choice) {
        case '1':
            find_doc(patient);
            break;
        case '2':
            book_appointment(patient);
            break;
        case '3':
            view_appointments(patient);
            break;
        case '4':
            edit_appointment(patient);
            break;
        case '5':
            delete_appointment(patient);
            break;
        case '6':
            clear_appointment_history(patient);
            break;
        case '7':
            edit_patient_info(patient);
            break;
        case '8':
            return; // exit the function and return to the calling function
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != '8');
}

void doctor_menu(Doctor* doctor, Appointment* appointments, int num_appointments, int& num_available_times) {
    char choice;
    do {
        cout << "*********" << endl;
        cout << "Welcome " << doctor->doc_name << " to Vezeeta!" << endl;
        std::cout << "1. View Appointments" << endl;
        std::cout << "2. Add Available Time" << endl;
        std::cout << "3. Remove Available Time" << endl;
        std::cout << "4. Edit basic info (username/password)" << endl;
        std::cout << "5. Edit  Available Time" << endl;
        std::cout << "6. Logout" << endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case '1':
            view_patients_with_appointments(doctor, appointments, num_appointments); // all function to view appointments
            break;
        case '2':
            add_available_time(doctor, num_available_times); // Call function to add available time
            break;
        case '3':
            remove_available_time(doctor); // Call function to remove available time
            break;
        case '4':
            edit_doctor_info(doctor);
            break;
        case '5':
            edit_available_time(doctor, num_available_times);
            break;
        case '6':
            std::cout << "Logging out..." << endl;
            return; // Exit the loop and return to the calling function
        default:
            std::cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != '6');
}
void register_doctor(Doctor doctors[], int& num_doctors) {
    Doctor doctor;
    std::cout << "Enter name: ";
    std::cin >> doctor.doc_name;
    while (true) {
        std::cout << "Enter email: ";
        std::cin >> doctor.acc.email;

        // Check if email already exists
        bool email_exists = false;
        for (int i = 0; i < num_doctors; i++) {
            if (doctors[i].acc.email == doctor.acc.email) {
                email_exists = true;
                break;
            }
        }
        if (email_exists) {
            std::cout << "Email already exists" << std::endl;
            continue;
        }

        // Check if email is empty or does not contain @ symbol
        bool valid_email = false;
        for (int i = 0; i < doctor.acc.email.size(); i++) {
            if (doctor.acc.email[i] == '@') {
                valid_email = true;
                break;
            }
        }
        if (doctor.acc.email.empty() || !valid_email) {
            std::cout << "Invalid email format. Please enter a valid email." << std::endl;
        }
        else {
            break;
        }
    }


    std::cout << "Enter username: ";
    std::cin >> doctor.acc.username;
    //make the password in *
    std::cout << "Enter password: ";
    char ch;
    while ((ch = _getch()) != '\r') {
        std::cout << '*';
        doctor.acc.password += ch;
    }
    std::cout << endl;

    // confirm the password
    do {
        std::cout << "Confirm password: ";
        doctor.acc.confirmPassword = "";
        char ch;
        while ((ch = _getch()) != '\r') //continue reading till you reach Enter
        {
            std::cout << '*';
            doctor.acc.confirmPassword += ch;
        }
        std::cout << endl;

        if (doctor.acc.password != doctor.acc.confirmPassword) {
            std::cout << "Passwords do not match. Please try again." << endl;
        }
    } while (doctor.acc.password != doctor.acc.confirmPassword);

    doctors[num_doctors++] = doctor;
}
// a function to register a patient
void register_patient(Patient patients[], int& num_patients) {
    Patient patient;
    cout << "Enter name: ";
    std::cin >> patient.pnt_name;
    while (true) {
        std::cout << "Enter email: ";
        std::cin >> patient.acc.email;

        // Check if email already exists
        bool email_exists = false;
        for (int i = 0; i < num_doctors; i++) {
            if (doctors[i].acc.email == patient.acc.email) {
                email_exists = true;
                break;
            }
        }
        if (email_exists) {
            std::cout << "Email already exists" << std::endl;
            continue;
        }

        // Check if email is empty or does not contain @ symbol
        bool valid_email = false;
        for (int i = 0; i < patient.acc.email.size(); i++) {
            if (patient.acc.email[i] == '@') {
                valid_email = true;
                break;
            }
        }
        if (patient.acc.email.empty() || !valid_email) {
            std::cout << "Invalid email format. Please enter a valid email." << std::endl;
        }
        else {
            break;
        }
    }
    std::cout << "Enter username: ";
    std::cin >> patient.acc.username;
    //make the password in *
    std::cout << "Enter password: ";
    char ch;
    while ((ch = _getch()) != '\r') {
        std::cout << '*';
        patient.acc.password += ch;
    }
    std::cout << endl;

    // confirm the password
    do {
        std::cout << "Confirm password: ";
        patient.acc.confirmPassword = "";
        char ch;
        while ((ch = _getch()) != '\r') //continue reading till you reach Enter
        {
            std::cout << '*';
            patient.acc.confirmPassword += ch;
        }
        std::cout << endl;

        if (patient.acc.password != patient.acc.confirmPassword) {
            std::cout << "Passwords do not match. Please try again." << endl;
        }
    } while (patient.acc.password != patient.acc.confirmPassword);
    int min_age = 18;
    int max_age = 95;
    std::cout << "Enter age: ";
    std::cin >> patient.age;
    while (patient.age < min_age || patient.age > max_age)
    {
        std::cout << "Age should be between " << min_age << " and " << max_age << ". Please enter a valid age." << std::endl;
        std::cout << "Enter age: ";
        std::cin >> patient.age;
    }
    patients[num_patients++] = patient;
}


//login functions 
bool doctor_login(Doctor doctors[], int num_doctors) {
    string email, password;
    std::cout << "Enter your email: ";
    std::cin >> email;
    std::cout << "Enter your password: ";
    char ch;
    while ((ch = _getch()) != '\r')
    {
        std::cout << '*';
        password += ch;
    }
    std::cout << endl;

    for (int i = 0; i < num_doctors; i++) {
        if (doctors[i].acc.email == email && doctors[i].acc.password == password) {
            std::cout << "Login successful!" << endl;
            return true;
        }
    }

    std::cout << "Invalid email / password" << endl;
    return false;
}
bool patient_login(Patient patients[], int num_patients)
{

    string email, password;
    std::cout << "Enter your email: ";
    std::cin >> email;
    std::cout << "Enter your password: ";
    char ch;
    while ((ch = _getch()) != '\r')
    {
        std::cout << '*';
        password += ch;
    }
    std::cout << endl;

    for (int i = 0; i < num_patients; i++) {
        if (patients[i].acc.email == email && patients[i].acc.password == password) {
            std::cout << "Login successful!" << endl;

            return true;
        }
    }

    std::cout << "Invalid email / password" << endl;
    return false;
}
void forget_pnt_password(Patient patients[], int num_patients) {
    string email;
    std::cout << "Enter your email: ";
    std::cin >> email;
    for (int i = 0; i < num_patients; i++) {
        if (patients[i].acc.email == email) {
            std::cout << "Account found!" << endl;
            std::cout << "Enter a new password: ";
            char ch;
            string new_password;
            while ((ch = _getch()) != '\r')
            {
                std::cout << '*';
                new_password += ch;
            }
            std::cout << endl;
            std::cout << "Confirm the new password: ";
            string confirm_password;
            while ((ch = _getch()) != '\r')
            {
                std::cout << '*';
                confirm_password += ch;
            }
            std::cout << endl;
            if (new_password == confirm_password) {
                patients[i].acc.password = new_password;
                std::cout << "Password updated successfully!" << endl;
            }
            else {
                std::cout << "Passwords do not match. Password not updated." << endl;
            }
            return;
        }
    }
    std::cout << "Email not found. Password not updated." << endl;
}


void forget_doc_password(Doctor doctors[], int num_doctors)
{
    string email;
    std::cout << "Enter your email: ";
    std::cin >> email;
    for (int i = 0; i < num_doctors; i++) {
        if (doctors[i].acc.email == email) {
            std::cout << "Account found!" << endl;
            std::cout << "Enter a new password: ";
            char ch;
            string new_password;
            while ((ch = _getch()) != '\r')
            {
                std::cout << '*';
                new_password += ch;
            }
            std::cout << endl;
            std::cout << "Confirm the new password: ";
            string confirm_password;
            while ((ch = _getch()) != '\r')
            {
                std::cout << '*';
                confirm_password += ch;
            }
            std::cout << endl;
            if (new_password == confirm_password) {
                doctors[i].acc.password = new_password;
                std::cout << "Password updated successfully!" << endl;
            }
            else {
                std::cout << "Passwords do not match. Password not updated." << endl;
            }
            return;
        }
    }
    std::cout << "Email not found. Password not updated." << endl;
}

void edit_doctor_info(Doctor* doctor) {
    char choice;

    std::cout << "1. Edit your username" << endl;
    std::cout << "2. Edit your password" << endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case '1':std::cout << "Enter new username: ";
        std::cin >> doctor->acc.username;

        break;

    case '2':std::cout << "Enter new password: ";
        std::cin >> doctor->acc.password;

        break;

    default:
        std::cout << "Invalid choice. Please try again." << endl;
        break;

    }
    std::cout << "your info updated successfully" << endl;


}
void edit_patient_info(Patient* patient) {
    char choice;

    std::cout << "1. Edit your username" << endl;
    std::cout << "2. Edit your password" << endl;
    std::cout << "3. Edit your age" << endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case '1':std::cout << "Enter new username: ";
        std::cin >> patient->acc.username;

        break;

    case '2':std::cout << "Enter new password: ";
        std::cin >> patient->acc.password;

        break;
    case '3':std::cout << "Enter new age: ";
        std::cin >> patient->age;
    default:
        std::cout << "Invalid choice. Please try again." << endl;
        break;

    }
    std::cout << "your info updated successfully" << endl;


}



void add_available_time(Doctor* doctor, int& num_available_times) {
    string date, time;
    std::cout << "Enter date (D/M): ";
    cin >> date;
    std::cout << "Enter time(H:M): ";
    std::cin >> time;

    if (doctor->num_avaliable_time == max_available_times) {
        std::cout << "Maximum number of available times reached." << std::endl;
        return;
    }

    doctor->available_times[doctor->num_avaliable_time] = date + " " + time;
    doctor->num_avaliable_time++;
    num_available_times++;
    std::cout << "Available time added successfully." << std::endl;
}

//num_available_times is passed as an argument instead of being a reference to a variable
void edit_available_time(Doctor* doctor, int& num_available_times) {
    string old_date, old_time;
    cout << "Enter old date: ";
    std::cin >> old_date;
    std::cout << "Enter old time: ";
    std::cin >> old_time;
    for (int i = 0; i < num_available_times; i++) {
        if (doctor->available_times[i] == old_date + " " + old_time) {
            string new_date, new_time;
            std::cout << "Enter new date: ";
            std::cin >> new_date;
            std::cout << "Enter new time:";
            std::cin >> new_time;
            doctor->available_times[i] = new_date + " " + new_time;
            std::cout << "Available time updated successfully." << std::endl;
            return;
        }
    }
    std::cout << "Could not find the specified time slot." << std::endl;
}
////appointments is an array of Appointment objects, and num_appointments is the number of elements in the array.
void view_patients_with_appointments(Doctor* doctor, Appointment* appointments, int num_appointments)
{
    if (appointments->doctor == 0)
    {
        cout << "You don't have any appointments." << endl;
        return;
    }
    std::cout << "Patients with appointments:" << endl;
    for (int i = 0; i < num_appointments; i++) {
        if (appointments[i].doctor == doctor) {
            std::cout << "Patient: " << appointments[i].patient->pnt_name << ", Date & Time: " << appointments[i].date << endl;
        }
    }
}
void find_doc(Patient* patient) {
    string docName;
    bool found = false;
    if (num_doctors == 0) {
        std::cout << "There are no doctors available. Returning to patient menu." << endl;
        return;
    }

    std::cout << "Enter the name of the doctor you want to find:";
    std::cin >> docName;
    for (int i = 0; i < num_doctors; i++)
    {
        if (doctors[i].doc_name == docName)
        {
            found = true;
            std::cout << "Doctor found:" << endl;
            std::cout << "Name: " << doctors[i].doc_name << endl;
            std::cout << "Email: " << doctors[i].acc.email << endl;
            std::cout << "Available Times: " << endl;
            for (int j = 0; j < doctors[i].num_avaliable_time; j++)
            {
                if (doctors[i].available_times[j] != "")//عشان لا يعرض ال 500 الي في الاراي كلهم 
                {
                    cout << "\t" << j + 1 << ". " << doctors[i].available_times[j] << endl;
                }
            }
            break;
        }
    }
    if (found == false) {
        cout << "Doctor not found." << endl;
    }
}

void view_appointments(Patient* patient) {
    if (patient->num_appointments == 0) {
        std::cout << "You don't have any appointments booked." << std::endl;
        return;
    }
    cout << "List of appointments booked by " << patient->pnt_name << ":" << endl;
    for (int i = 0; i < num_appointments; i++)
    {
        cout << i + 1 << ". " << appointments[i].doctor->doc_name << " on "
            << appointments[i].date << endl;
    }
}



void remove_available_time(Doctor* doctor) {
    if (doctor->num_avaliable_time == 0) {
        cout << "You don't have any available times to remove." << endl;
        return;
    }

    cout << "Please select the available time you want to remove:" << endl;
    for (int i = 0; i < doctor->num_avaliable_time; i++) {
        cout << i + 1 << ". " << doctor->available_times[i] << endl;
    }

    int choice;
    do {
        cin >> choice;
        if (choice < 1 || choice > doctor->num_avaliable_time) {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice < 1 || choice > doctor->num_avaliable_time);

    // Shift remaining elements to fill the empty space in ythe array since we removed an element
    for (int i = choice - 1; i < doctor->num_avaliable_time - 1; i++) {
        doctor->available_times[i] = doctor->available_times[i + 1];
    }
    doctor->num_avaliable_time--;

    cout << "Available time removed successfully." << endl;

    char another_time;
    cout << "Do you want to remove another available time? (y/n)" << endl;
    cin >> another_time;
    if (another_time == 'y') {
        remove_available_time(doctor);
    }
    else if (another_time == 'n') {
        return;
    }
    else {
        cout << "Invalid choice. Returning to doctor menu." << endl;
        return;
    }
}


void delete_appointment(Patient* patient) {
    if (patient->num_appointments == 0) {
        cout << "You don't have any appointments to remove." << endl;
        return;
    }
    // Display list of appointments booked by the patient
    cout << "List of appointments booked by " << patient->pnt_name << ":" << endl;
    for (int i = 0; i < num_appointments; i++)
    {
        cout << i + 1 << ". " << appointments[i].doctor->doc_name << " on "
            << appointments[i].date << endl;
    }
    // Prompt the user to select an appointment to delete
    std::cout << "Select an appointment to delete:" << std::endl;
    int appointment_choice;
    std::cin >> appointment_choice;
    if (appointment_choice < 1 || appointment_choice > patient->num_appointments) {
        std::cout << "Invalid appointment choice." << std::endl;
        return;
    }
    appointment_choice--;
    // Get the appointment to be deleted
    Appointment* appointment = patient->appointments[appointment_choice];
    // Remove the appointment from the appointments array
    for (int i = 0; i < num_appointments; i++) {
        if (&appointments[i] == appointment) {
            // Shift all appointments after the deleted appointment back by one
            for (int j = i; j < num_appointments - 1; j++) {
                appointments[j] = appointments[j + 1];
            }
            num_appointments--;
            break;
        }
    }
    // Add the appointment's time slot back to the doctor's available times
    Doctor* doctor = appointment->doctor;
    doctor->available_times[doctor->num_avaliable_time] = appointment->time;
    doctor->num_avaliable_time++;
    // Delete the appointment from the patient's list of appointments
    for (int i = appointment_choice; i < patient->num_appointments - 1; i++) {
        patient->appointments[i] = patient->appointments[i + 1];
    }
    patient->num_appointments--;
    std::cout << "Appointment deleted successfully." << std::endl;

    char another_appointment;
    cout << "Do you want to remove another appointment? (y/n)" << endl;
    cin >> another_appointment;
    if (another_appointment == 'y') {
        delete_appointment(patient);
    }
    else if (another_appointment == 'n') {
        return;
    }
    else {
        cout << "Invalid choice. Returning to patient menu." << endl;
        return;
    }

}

void clear_appointment_history(Patient* patient) {
    if (patient->num_appointments == 0) {
        std::cout << "No appointments to clear." << std::endl;
        return;
    }

    for (int i = 0; i < num_appointments; i++) {
        Appointment* appointment = &appointments[i];
        if (appointment->patient == patient) {
            Doctor* doctor = appointment->doctor;
            doctor->num_avaliable_time++;
            doctor->available_times[doctor->num_avaliable_time - 1] = appointment->time;
            for (int j = i; j < num_appointments - 1; j++) {
                appointments[j] = appointments[j + 1];
            }
            num_appointments--;
            i--;
        }
    }

    patient->num_appointments = 0;

    std::cout << "All appointments cleared." << std::endl;
}

void book_appointment(Patient* patient) {
    // Display list of doctors and their available time slots
    std::cout << "List of available doctors and their available time slots:" << std::endl;
    for (int i = 0; i < num_doctors; i++)
    {
        std::cout << i + 1 << ": " << doctors[i].doc_name << std::endl;
        std::cout << "   Available time slots:" << std::endl;
        for (int j = 0; j < doctors[i].num_avaliable_time; j++)
        {

            cout << "\t" << j + 1 << ". " << doctors[i].available_times[j] << endl;

        }
    }
    // Prompt the user to select a doctor and a time slot
    std::cout << "Select a doctor and an available time slot:" << std::endl;
    int doctor_choice, time_choice;
    std::cin >> doctor_choice >> time_choice;
    if (doctor_choice < 1 || doctor_choice > num_doctors) {
        std::cout << "Invalid doctor choice." << std::endl;
        return;
    }
    Doctor* doctor = &doctors[doctor_choice - 1];
    if (time_choice < 1 || time_choice > doctor->num_avaliable_time) {
        std::cout << "Invalid time choice." << std::endl;
        return;
    }
    // Prompt the user to enter their email address to verify their identity
    std::cout << "Enter your email address: ";
    string email;
    std::cin >> email;
    // Find the patient account corresponding to the entered email address
    int patient_index = -1;
    for (int i = 0; i < num_patients; i++) {
        if (patients[i].acc.email == email) {
            patient_index = i;
            break;
        }
    }
    if (patient_index == -1) {
        std::cout << "No patient account found for the entered email address." << std::endl;
        return;
    }


    // Create a new appointment
    if (num_appointments == max_appointments) {
        std::cout << "Maximum number of appointments reached." << std::endl;
        return;
    }
    Appointment* appointment = &appointments[num_appointments];
    appointment->doctor = doctor;
    appointment->patient = &patients[patient_index];
    appointment->date = doctor->available_times[time_choice - 1];
    appointment->time = doctor->available_times[time_choice - 1];
    doctor->num_avaliable_time--;
    for (int i = time_choice - 1; i < doctor->num_avaliable_time; i++) {
        doctor->available_times[i] = doctor->available_times[i + 1];
    }
    num_appointments++;
    // Store the appointment in the patient's appointments array
    if (patient->num_appointments == max_appointments) {
        std::cout << "Maximum number of appointments reached." << std::endl;
        return;
    }
    Appointment** patient_appointments = patient->appointments;
    patient_appointments[patient->num_appointments] = appointment;
    patient->num_appointments++;

    cout << "Appointment booked successfully." << endl;

    char another_appointment;
    cout << "Do you want to book another appointment? (y/n)" << endl;
    cin >> another_appointment;

    if (another_appointment == 'y') {
        book_appointment(patient);
    }
    else if (another_appointment == 'n') {
        return;
    }
    else {
        cout << "Invalid choice. Returning to patient menu." << endl;
        return;
    }
}



void edit_appointment(Patient* patient)
{
    if (num_appointments == 0) {
        cout << "You have no appointments to edit" << endl;
        return;
    }

    cout << "Here are your appointments:" << endl;
    for (int i = 0; i < num_appointments; i++) {
        cout << i + 1 << ". " << appointments[i].doctor->doc_name << " on "
            << appointments[i].date << endl;
    }

    cout << "Enter the number of the appointment you want to edit: ";
    int old_time_num;
    cin >> old_time_num;

    if (old_time_num < 1 || old_time_num > num_appointments)
    {
        cout << "Invalid appointment number" << endl;
        return;
    }
    Appointment* old_appointment = &appointments[old_time_num - 1];

    // display available time slots for the doctor
    cout << "Available time slots for " << old_appointment->doctor->doc_name << ":" << endl;
    if (old_appointment->doctor->num_avaliable_time == 0)
    {
        cout << "Sorry, the doctor does not have any available time slots." << endl;
        return;
    }
    for (int i = 0; i < old_appointment->doctor->num_avaliable_time; i++)
    {
        cout << i + 1 << ". " << old_appointment->doctor->available_times[i] << endl;
    }


    //choose a new time slot
    cout << "Enter the number of the new time slot: ";
    int new_time_num;
    cin >> new_time_num;

    if (new_time_num < 1 || new_time_num > old_appointment->doctor->num_avaliable_time)
    {
        cout << "Invalid time slot number" << endl;
        return;
    }

    // update the appointment with new time 
    Appointment new_appointment = *old_appointment;
    new_appointment.date = old_appointment->doctor->available_times[new_time_num - 1];
    new_appointment.time = old_appointment->doctor->available_times[new_time_num - 1];
    old_appointment->doctor->available_times[old_appointment->doctor->num_avaliable_time] = old_appointment->date + " " + old_appointment->time;
    old_appointment->doctor->num_avaliable_time++;
    *old_appointment = new_appointment;

    cout << "Appointment updated successfully" << endl;
}