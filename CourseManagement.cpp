#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
class Student;
class Node{
    public:
    int StudentID;
    string StudentName;
    Node* before;
    Node* next;
    Node(){

        next=nullptr;
        before=nullptr;
    }
};
class CustomStudentList
{
private:
    Node* head;
    Node* tail;
    int size;
public:
    CustomStudentList(){
        head=nullptr;
        size=0;
    }
    bool Emptylist(){
        return head==nullptr;
    
    }
    void addStudentfront(int id,string name){
        Node* temp=new Node();
        temp->StudentID=id;
        temp->StudentName=name;
        if(Emptylist()){
            temp->next=nullptr;
            temp->before=nullptr;
            head=temp;
            tail=head;
        }
        else{
            temp->next=head;
            temp->before=nullptr;
            head=temp;
        }
        size++;
    }
    void addStudentlast(int id,string name){
        Node* temp=new Node();
        temp->StudentID=id;
        temp->StudentName=name;
        if(Emptylist()){
            temp->next=nullptr;
            temp->before=nullptr;
            head=temp;
            tail=head;
        }
        else{
                       
            temp->next=nullptr;
            temp->before=tail;
            tail->next=temp;
            tail=temp;
        }
        size++;
    }
    Node* SearchID(int id){
        if(Emptylist()){
            cout<<"The list is Empty"<<"\n";
            return nullptr;
        }
        else{
            Node* ser=head;
            while (ser!=nullptr)
            {
                if(ser->StudentID==id){
                    return ser;
                }
                ser=ser->next;
            }
            return nullptr;
            
        }
    }
    Node* SearchName(string name){
        if(Emptylist()){
            cout<<"The list is Empty"<<"\n";
            return nullptr;
        }
        else{
            Node* ser=head;
            while (ser!=nullptr)
            {
                if(ser->StudentName==name){
                    return ser;
                }
                ser=ser->next;
            }
            return nullptr;
            
        }
    }
    bool removeStudent(Node* ser){
        if(ser==nullptr){
            return false;
        }
        else if(size==1){
            delete ser;
            head=nullptr;
            tail=nullptr;
            size--;
            return true;
        }
        else if(ser==head){
            Node* temp=head;
            head=head->next;
            head->before=nullptr;
            delete temp;
            size--;
            return true;
        }
        else if(ser==tail){
            Node* temp=tail;
            tail=tail->before;
            tail->next=nullptr;
            delete temp;
            size--;
            return true;
        }
        else{
            Node* back=ser->before;
            Node* front=ser->next;
            back->next=front;
            front->before=back;
            delete ser;
            size--;
            return true;
        }
    } 
    bool removestudentID(int id){
        Node* ser=SearchID(id);
        return removeStudent(ser);
    }
 bool removestudentName(string name){
        Node* ser=SearchName(name);
        return removeStudent(ser);
    }   
    void displayfront(){
        Node* temp=head;
        while(temp!=nullptr){
            cout<<"Student ID: "<<temp->StudentID<<" Student Name: "<<temp->StudentName<<"\n";
            temp=temp->next;
        }
    } 
    void displayback(){
        Node* temp=tail;
        while(temp!=nullptr){
            cout<<"Student ID: "<<temp->StudentID<<" Student Name: "<<temp->StudentName<<"\n";
            temp=temp->before;
        }
    } 
    int getSize(){
        return size;
    }
    ~CustomStudentList(){
        while(head!=nullptr){
            Node* temp=head;
            head=head->next;
            delete temp;
        }
    }
};
class User{
    protected:
    int ID;
    string Name;
    string Email;
    string Password;
    public:
    User(int id,string name,string email,string password){
        ID=id;
        Name=name;
        Email=email;
        Password=password;
    }
    virtual void displayMenu()=0;
    int getID(){
        return ID;
    }
    string getName(){
        return Name;
    }
    string getEmail(){
        return Email;
    }
    string getpassword(){
        return Password;
    }
    virtual ~User(){}
};
class Course{
        private:
        int courseID;
        string courseNAme;
        int MaxCapacity;
        CustomStudentList EnrolledStudent;
        int studentIDs[100];
        double studentGrades[100];
        int studentCount;
        int instructorID;
        public:
        Course(int id,string name,int capacity,int instID):courseID(id),courseNAme(name),MaxCapacity(capacity),studentCount(0),instructorID(instID){}
        void setGrade(int studentID,double grade){
            for (int i = 0; i < studentCount; i++)
            {
                if(studentIDs[i]==studentID){
                    studentGrades[i]=grade;
                    return;
                }
            }
            if(studentCount<100){
                studentIDs[studentCount]=studentID;
                studentGrades[studentCount]=grade;
                studentCount++;
            }
        }
        bool isStudentEnrroled(int studentID){
            return EnrolledStudent.SearchID(studentID)!=nullptr;
        }
        double getGrade(int studentID){
            for (int i = 0; i < studentCount; i++)
            {
                if(studentIDs[i]==studentID){
                    return studentGrades[i];
                }
            }
            return -1;
        }
        
        void displayAllGrades() {
    if (studentCount == 0) {
        cout << "No grades recorded yet.\n";
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        cout << "Student ID: " << studentIDs[i] << " | Grade: " << studentGrades[i] << "\n";
    }
}
        int getCourseID(){
            return courseID;
        }
        int getInstructorID(){
            return instructorID;
        }
        string getCourseName(){
            return courseNAme;
        }
        int getMaxCapacity(){
            return MaxCapacity;
        }
        bool addStudent(int id,string name){
            bool found = false;
            for(int i = 0; i < studentCount; i++) {
                if (studentIDs[i] == id) {
                    found = true;
                    break;
                }
            }
            if (found) {
                cout << "__Student is already enrolled in this course__" << "\n";
                return false; }

           if (EnrolledStudent.getSize() < MaxCapacity) {
        EnrolledStudent.addStudentlast(id, name);
            studentIDs[studentCount] = id;
            studentGrades[studentCount] = 0.0;
            studentCount++;
        return true;
    }
    return false;
        }

void saveStudent(ofstream& file) {
    file << studentCount << "\n";

    for (int i = 0; i < studentCount; i++) {
        Node* studentNode = EnrolledStudent.SearchID(studentIDs[i]);

        string studentName =
            (studentNode != nullptr)
            ? studentNode->StudentName
            : "Unknown";

        file << studentIDs[i] << " "
             << quoted(studentName) << " "
             << studentGrades[i] << "\n";
    }
}

void loadStudent(ifstream& file) {
    int count;

    if (!(file >> count) || count < 0 || count > 100) {
        cout << "Invalid student count in course data\n";
        return;
    }

    studentCount = 0;

    for (int i = 0; i < count; i++) {
        int id;
        string name;
        double grade;

        if (!(file >> id >> quoted(name) >> grade)) {
            cout << "Error reading enrolled student data\n";
            studentCount = 0;
            return;
        }

        studentIDs[studentCount] = id;
        studentGrades[studentCount] = grade;
        studentCount++;

        EnrolledStudent.addStudentlast(id, name);
    }
}
    };
    class SystemManager;
    class Student:public User{
    private:
    double GPA;
    Course* EnrolledCourses[10];
    int EnrolledCourseCount;
    public:
    Student(int id,string name,string email,string password,double gpa):User(id,name, email, password){
        GPA=gpa;
        EnrolledCourseCount=0;
    }
    void displayMenu ()override{
        cout<<"1_Enroll in Courses"<<"\n";
        cout<<"2_View Enrolled Courses"<<"\n";
        cout<<"3_View Grades"<<"\n";
        cout<<"4_Logout"<<"\n";
        cout<<"Enter your choice: "<<"\n";

        
    }
    void HandleMenu(SystemManager& Sys);
    double getGPA(){
        return GPA;
    }
    void addEnrolledCourseDirectly(Course* c){
        if(EnrolledCourseCount<10){
            EnrolledCourses[EnrolledCourseCount]=c;
            EnrolledCourseCount++;
        }
    }
};
class Instructor:public User{
    private:
    string Department;
    int instructorID;
    public:
    Instructor(int id,string name,string email,string password,string depart):User(id,name, email, password){
        Department=depart;
        instructorID=id;
    }
    void displayMenu()override{
        cout<<"1_create Course"<<"\n";
        cout<<"2_View  MY Courses"<<"\n";
        cout<<"3_Add student to Course"<<"\n";
        cout<<"4_View Student Grades"<<"\n";
        cout<<"5_Set Grade for Student"<<"\n";
        cout<<"6_Logout"<<"\n";
        cout<<"Enter your choice: "<<"\n";
    }
    void HandleMenu(SystemManager& Sys);
    string getDepartment(){
        return Department;
    }
    int getInstructorID(){
        return instructorID;
    }
};
class Admin:public User{
        public:
        Admin(int id,string name,string email,string password):User(id,name, email, password){}
        void displayMenu() override{
            cout<<"1_Add Student"<<"\n";
            cout<<"2_Remove Student"<<"\n";
            cout<<"3_Add Instructor"<<"\n";
            cout<<"4_Remove Instructor"<<"\n";
            cout<<"5_Add Course"<<"\n";
            cout<<"6_Remove Course"<<"\n";
            cout<<"7_Add a new Admin"<<"\n";
            cout<<"8_Logout"<<"\n";
            cout<<"Enter your choice: "<<"\n";
        }
        void HandleMenu(SystemManager& Sys);
    };
class SystemManager{
    private:
    CustomStudentList* System;
    User* users[100];
    Course* courses[30];
    int Usercount;
    int coursecount;
    public:

void saveData() {
    ofstream userFile("users.txt");

    if (!userFile.is_open()) {
        cout << "Error opening users.txt for saving\n";
        return;
    }

    for (int i = 0; i < Usercount; i++) {
        Student* s = dynamic_cast<Student*>(users[i]);
        Instructor* inst = dynamic_cast<Instructor*>(users[i]);
        Admin* a = dynamic_cast<Admin*>(users[i]);

        if (s) {
            userFile << "STUDENT " << s->getID() << " "
                     << quoted(s->getName()) << " "
                     << quoted(s->getEmail()) << " "
                     << quoted(s->getpassword()) << " "
                     << s->getGPA() << "\n";
        }
        else if (inst) {
            userFile << "INSTRUCTOR " << inst->getID() << " "
                     << quoted(inst->getName()) << " "
                     << quoted(inst->getEmail()) << " "
                     << quoted(inst->getpassword()) << " "
                     << quoted(inst->getDepartment()) << "\n";
        }
        else if (a) {
            userFile << "ADMIN " << a->getID() << " "
                     << quoted(a->getName()) << " "
                     << quoted(a->getEmail()) << " "
                     << quoted(a->getpassword()) << "\n";
        }
    }

    userFile.close();

    ofstream courseFile("courses.txt");

    if (!courseFile.is_open()) {
        cout << "Error opening courses.txt for saving\n";
        return;
    }

    for (int i = 0; i < coursecount; i++) {
        courseFile << courses[i]->getCourseID() << "\n"
                   << quoted(courses[i]->getCourseName()) << "\n"
                   << courses[i]->getMaxCapacity() << "\n"
                   << courses[i]->getInstructorID() << "\n";

        courses[i]->saveStudent(courseFile);
    }

    courseFile.close();
}


void loadData() {
    ifstream userFile("users.txt");

    if (userFile.is_open()) {
        string type;

        while (userFile >> type) {
            if (type == "STUDENT") {
                int id;
                string name, Email, password;
                double gpa;

                if (!(userFile >> id >> quoted(name)
                      >> quoted(Email) >> quoted(password) >> gpa)) {
                    cout << "Error reading student data\n";
                    break;
                }

                AddUser(new Student(id, name, Email, password, gpa));
            }
            else if (type == "INSTRUCTOR") {
                int id;
                string name, Email, password, dept;

                if (!(userFile >> id >> quoted(name)
                      >> quoted(Email) >> quoted(password)
                      >> quoted(dept))) {
                    cout << "Error reading instructor data\n";
                    break;
                }

                AddUser(new Instructor(id, name, Email, password, dept));
            }
            else if (type == "ADMIN") {
                int id;
                string name, Email, password;

                if (!(userFile >> id >> quoted(name)
                      >> quoted(Email) >> quoted(password))) {
                    cout << "Error reading admin data\n";
                    break;
                }

                AddUser(new Admin(id, name, Email, password));
            }
            else {
                cout << "Unknown user type: " << type << "\n";
                break;
            }
        }

        userFile.close();
    }

    ifstream courseFile("courses.txt");

    if (courseFile.is_open()) {
        int id, cap, instID;
        string name;

        while (courseFile >> id) {
            if (!(courseFile >> quoted(name) >> cap >> instID)) {
                cout << "Error reading course data\n";
                break;
            }

            Course* c = new Course(id, name, cap, instID);
            addCourse(c);

            c->loadStudent(courseFile);

            for (int i = 0; i < Usercount; i++) {
                Student* st = dynamic_cast<Student*>(users[i]);

                if (st != nullptr && c->isStudentEnrroled(st->getID())) {
                    st->addEnrolledCourseDirectly(c);
                }
            }
        }

        courseFile.close();
    }
}
  SystemManager(){
        Usercount=0;
        coursecount=0;
        System=new CustomStudentList();
        loadData();
    }
    
    int getCourseCount(){
        return coursecount;
    }
    Course* loopCourse(int i){
            return courses[i];
    }
    User* login(int id,string password){
        for (int i = 0; i < Usercount; i++)
        {
            if(users[i]->getID()==id && users[i]->getpassword()==password){
                cout<<"__Welcome__"<<"\n";
                return users[i];
            }
            
        }
        cout<<"__Wrong ID or Password__";
        return nullptr;
    }
     bool IsUserregisterbyID(int id){
        for(int i=0;i<Usercount;i++){
            if(users[i]->getID()==id){
                return true;
            }
        }
        return false;
    }
    void AddUser(User* u){
    if(Usercount>=100){
        cout<<"System is full"<<"\n";
        delete u;
        return;
        }
    if(IsUserregisterbyID(u->getID())){
        cout<<"__User with this ID already exists__"<<"\n";
        delete u;
        return;
    }
    users[Usercount]=u;
    Usercount++;
    cout<<"__User Added Successfully__"<<"\n";
    System->addStudentlast(u->getID(),u->getName());
    }
    bool IsUserregisterbyName(string name){
        for(int i=0;i<Usercount;i++){
            if(users[i]->getName()==name){
                return true;
            }
        }
        return false;
    }
    void RemoveUserByID(int id){
        for (int i = 0; i < Usercount; i++)
        {
            if(users[i]->getID()==id){
                delete users[i];
                for (int j = i; j < Usercount-1; j++)
                {
                    users[j]=users[j+1];
                }
                Usercount--;
                System->removestudentID(id);
                break;
            }
            
        }
    }
    void RemoveUserByName(string name){
        for (int i = 0; i < Usercount; i++)
        {
            if(users[i]->getName()==name){
                delete users[i];
                for (int j = i; j < Usercount-1; j++)
                {
                    users[j]=users[j+1];
                }
                Usercount--;
                System->removestudentName(name);
                break;
            }

            
        }
    }
    void PrintUserlistReverse(){
        System->displayback();
    }
void PrintUserlist(){
        System->displayfront();
    }
    void addCourse(Course* c){
        if(coursecount<30){
            courses[coursecount]=c;
            coursecount++;
        }
    }
    void removeCourse(int id){
        for (int i = 0; i < coursecount; i++)
        {
            if(courses[i]->getCourseID()==id){
                delete courses[i];
                for (int j = i; j < coursecount-1; j++)
                {
                    courses[j]=courses[j+1];
                }
                coursecount--;
                break;
            }
            
        }
    }
    Course* searchCourse(int id){
        for (int i = 0; i < coursecount; i++)
        {
            if(courses[i]->getCourseID()==id){
                cout<<"Course ID: "<<courses[i]->getCourseID()<<" Course Name: "<<courses[i]->getCourseName()<<"\n";
                return courses[i];
            }
            
        }
        cout<<"__Course not found__"<<"\n";
        return nullptr;
    }
    
    ~SystemManager() {
        saveData();
        for (int i = 0; i < Usercount; i++) {
            delete users[i];
        }
        for (int i = 0; i < coursecount; i++) {
            delete courses[i];
        }
        delete System;
    }

};
void Student::HandleMenu(SystemManager& Sys){
        int i=0;
        while(i!=4){
        displayMenu();
        cin>>i;
        if(i==1){
            int id;
            string name;
            cout<<"Enter Course ID: "<<"\n";
            cin>>id;
            cout<<"Enter Course Name: "<<"\n";
            getline(cin>>ws,name);
            Course* foundCourse = Sys.searchCourse(id);
            if(foundCourse && foundCourse->getCourseName() == name){
                if(EnrolledCourseCount<10){
                    if(foundCourse->addStudent(ID,Name)){
                    EnrolledCourses[EnrolledCourseCount] = foundCourse;
                    EnrolledCourseCount++;
                    cout<<"__Course Enrolled Successfully__"<<"\n";}
                    else{
                        cout<<"__Course is Full__"<<"\n";
                    }
                }
                else{
                    cout<<"__You have reached the maximum number of enrolled courses__"<<"\n";
                }
            }
          
        }
        else if(i==2){
            cout<<"__Enrolled Courses__"<<"\n";
            for (int j = 0; j < EnrolledCourseCount; j++)
            {
                cout<<"Course ID: "<<EnrolledCourses[j]->getCourseID()<<" Course Name: "<<EnrolledCourses[j]->getCourseName()<<"\n";
            }
        }
        else if(i==3){
            cout<<"__View Grades__"<<"\n";
            for (int j = 0; j < EnrolledCourseCount; j++)
            {
                double grade = EnrolledCourses[j]->getGrade(ID);
                if(grade != -1){
                    cout<<"Course ID: "<<EnrolledCourses[j]->getCourseID()<<" Course Name: "<<EnrolledCourses[j]->getCourseName()<<" Grade: "<<grade<<"\n";
                }
                else{
                    cout<<"Course ID: "<<EnrolledCourses[j]->getCourseID()<<" Course Name: "<<EnrolledCourses[j]->getCourseName()<<" Grade: Not Available"<<"\n";
                }
            }
        }
        else if(i==4){
            cout<<"Logging out..."<<"\n";
            return;
        }
        else{
            cout<<"Invalid choice. Please try again."<<"\n";
        }
    }
}
void Admin::HandleMenu(SystemManager& Sys){
                int i=0;
            while(i!=8){
            displayMenu();
            cin>>i;
            if(i==1){
                int id;
                string name,email,password;
                cout<<"Enter Student ID: "<<"\n";
                cin>>id;
                cout<<"Enter Student Name: "<<"\n";
                getline(cin>>ws,name);
                cout<<"Enter Student Email: "<<"\n";
                getline(cin>>ws,email);
                cout<<"Enter Student Password: "<<"\n";
                getline(cin>>ws,password);
                Student* newStudent = new Student(id,name,email,password,0.0);
                Sys.AddUser(newStudent);
            }
            else if(i==2){
                int id;
                cout<<"Enter Student ID to remove: "<<"\n";
                cin>>id;
                Sys.RemoveUserByID(id);
            }
            else if(i==3){
                int id;
                string name,email,password,department;
                cout<<"Enter Instructor ID: "<<"\n";
                cin>>id;
                cout<<"Enter Instructor Name: "<<"\n";
                getline(cin>>ws,name);
                cout<<"Enter Instructor Email: "<<"\n";
                getline(cin>>ws,email);
                cout<<"Enter Instructor Password: "<<"\n";
                getline(cin>>ws,password);
                cout<<"Enter Instructor Department: "<<"\n";
                getline(cin>>ws,department);
                Instructor* newInstructor = new Instructor(id,name,email,password,department);
                Sys.AddUser(newInstructor);
            }
            else if(i==4){
                int id;
                cout<<"Enter Instructor ID to remove: "<<"\n";
                cin>>id;
                Sys.RemoveUserByID(id);
            }
            else if(i==5){
                
                int id,instid;
                string name;
                int capacity;
                cout<<"Enter Course ID: "<<"\n";
                cin>>id;
                cout<<"Enter Course Name: "<<"\n";
                getline(cin>>ws,name);
                cout<<"Enter Course Capacity: "<<"\n";
                cin>>capacity;
                cout<<"Enter Instructor ID: "<<"\n";
                cin>>instid;
                Course* newCourse = new Course(id,name,capacity,instid);
                Sys.addCourse(newCourse);
                
            }
            else if(i==6){
                int id;
                cout<<"Enter Course ID to remove: "<<"\n";
                cin>>id;
                Sys.removeCourse(id);
            }
            else if(i==7){
                int id;
                string name,email,password;
                cout<<"Enter Admin ID: "<<"\n";
                cin>>id;
                cout<<"Enter Admin Name: "<<"\n";
                getline(cin>>ws,name);
                cout<<"Enter Admin Email: "<<"\n";
                getline(cin>>ws,email);
                cout<<"Enter Admin Password: "<<"\n";
                getline(cin>>ws,password);
                Admin* newAdmin = new Admin(id,name,email,password);
                Sys.AddUser(newAdmin);
            }
            else if(i==8){
                cout<<"Logging out..."<<"\n";
                return;
            }
            else{
                cout<<"Invalid choice. Please try again."<<"\n";
            }
        }
    }
void Instructor::HandleMenu(SystemManager& Sys){        
        int i=0;
        while(i!=6){
        displayMenu();
        cin>>i;
        if(i==1){
            int id;
            string name;
            int capacity;
            cout<<"Enter Course ID: "<<"\n";
            cin>>id;
            cout<<"Enter Course Name: "<<"\n";
            getline(cin>>ws,name);
            cout<<"Enter Course Capacity: "<<"\n";
            cin>>capacity;
            Course* newCourse = new Course(id,name,capacity,instructorID);
            Sys.addCourse(newCourse);
        }
        else if(i==2){
            cout<<"__My Courses__"<<"\n";
            for (int j = 0; j <Sys.getCourseCount(); j++)
            {
                if(Sys.loopCourse(j)->getInstructorID()==instructorID){
                    cout<<"Course ID: "<<Sys.loopCourse(j)->getCourseID()<<" Course Name: "<<Sys.loopCourse(j)->getCourseName()<<"\n";
                }
            }
        }
        else if(i==3){
            int courseID,studentID;
            string studentName;
            cout<<"Enter Course ID: "<<"\n";
            cin>>courseID;
            cout<<"Enter Student ID: "<<"\n";
            cin>>studentID;
            cout<<"Enter Student Name: "<<"\n";
            getline(cin>>ws,studentName);
            Course* foundCourse = Sys.searchCourse(courseID);
            if(foundCourse && foundCourse->getInstructorID()==instructorID){
                if(foundCourse->addStudent(studentID,studentName)){
                    cout<<"__Student Added Successfully__"<<"\n";
                }
                else{
                    cout<<"__Course is Full__"<<"\n";
                }
            }
            else{
                cout<<"__Course not found or you are not the instructor of this course__"<<"\n";
            }
        }
        else if(i==4){
            int courseID;
            cout<<"Enter Course ID: "<<"\n";
            cin>>courseID;
            Course* foundCourse = Sys.searchCourse(courseID);
            if(foundCourse && foundCourse->getInstructorID()==instructorID){
                cout<<"__Student Grades__"<<"\n";
               foundCourse->displayAllGrades();
            }
            else{
                cout<<"__Course not found or you are not the instructor of this course__"<<"\n";
            }
        }
        else if(i==5){
            int courseID,studentID;
            double grade;
            cout<<"Enter Course ID: "<<"\n";
            cin>>courseID;
            cout<<"Enter Student ID: "<<"\n";
            cin>>studentID;
            cout<<"Enter Grade: "<<"\n";
            cin>>grade;
            Course* foundCourse = Sys.searchCourse(courseID);
            if(foundCourse && foundCourse->getInstructorID()==instructorID){
                if(foundCourse->isStudentEnrroled(studentID)){
                    foundCourse->setGrade(studentID,grade);
                    cout<<"__Grade Set Successfully__"<<"\n";
                }
                else{
                    cout<<"__Student is not enrolled in this course__"<<"\n";
                }
            }
            else{
                cout<<"__Course not found or you are not the instructor of this course__"<<"\n";
            }
        }
        else if(i==6){
            cout<<"Logging out..."<<"\n";
            return;
        }
        else{
            cout<<"Invalid choice. Please try again."<<"\n";
        }
    }
}
int main(){
    SystemManager a;
    Admin* newAdmin = new Admin(1000,"Admin","admin@example.com","1234");
    a.AddUser(newAdmin);
    int choice;
    do {
        cout<<"__Welcome to the Course Management System__"<<"\n";
        cout<<" 1_Login"<<"\n";
        cout<<" 2_Register"<<"\n";
        cout<<" 3_Exit"<<"\n";
        cin>>choice;
    if(choice==2)
    {int choi;
        cout<<"1_Student"<<"\n";
        cout<<"2_Instructor"<<"\n";
        cout<<"Enter your choice: "<<"\n";
        cin>>choi;
        if(choi==1){
            int id;
            string name,email,password;
            cout<<"Enter your ID: "<<"\n";
            cin>>id;
            cout<<"Enter your Name: "<<"\n";
            getline(cin>>ws,name);
            cout<<"Enter your Email: "<<"\n";
            getline(cin>>ws,email);
            cout<<"Enter your Password: "<<"\n";
            getline(cin>>ws,password);
            Student* newStudent = new Student(id,name,email,password,0.0);
            a.AddUser(newStudent);
        }
        else if(choi==2){
            int id;
            string name,email,password,department;
            cout<<"Enter your ID: "<<"\n";
            cin>>id;
            cout<<"Enter your Name: "<<"\n";
            getline(cin>>ws,name);
            cout<<"Enter your Email: "<<"\n";
            getline(cin>>ws,email);
            cout<<"Enter your Password: "<<"\n";
            getline(cin>>ws,password);
            cout<<"Enter your Department: "<<"\n";
            getline(cin>>ws,department);
            Instructor* newInstructor = new Instructor(id,name,email,password,department);
            a.AddUser(newInstructor);
        }
        else{cout<<"Unvailable Choice"<<"\n";}
    
    }
    else if(choice==1){
        int id;
        string password;
        cout<<"Enter your ID: "<<"\n";
        cin>>id;
        cout<<"Enter your Password: "<<"\n";
        getline(cin>>ws,password);
        User* loggedInUser = a.login(id,password);
        if(loggedInUser!=nullptr){
            Student* studentUser = dynamic_cast<Student*>(loggedInUser);
            Admin* adminUser = dynamic_cast<Admin*>(loggedInUser);
            Instructor* instructorUser = dynamic_cast<Instructor*>(loggedInUser);
            if(studentUser!=nullptr){
                studentUser->HandleMenu(a);
            }
            else if(adminUser!=nullptr){
                adminUser->HandleMenu(a);
            }
            else if(instructorUser!=nullptr){
                instructorUser->HandleMenu(a);
            }
        }
    } 
}while(choice!=3);
    }
