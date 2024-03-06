#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <thread>

class Agent {
public:
    Agent(POINT location, std::string str, std::string role, int id) {
        this->location = location;
        this->name = str;
        this->role = role;
        this->id = id;
    }
    POINT getLocation() const { return location; }
    std::string getName() const { return name; }
    std::string getRole() const { return role; }
    int getID() const { return id; }

private:
    POINT location;
    std::string name;
    std::string role;
    int id;
};
class Agents {
public:
    static const int AGENT_COUNT = 23; //Current Ammount of Agents
    static Agent* resolveAgent(int id) {
        POINT location = { 0,0 };
        std::string name = "";
        std::string role = "";
        switch (id) {
        case 1:
            location = { 625,841 };
            name = "Brimstone";
            role = "Controller";
            break;
        case 2:
            location = { 876,1008 };
            name = "Viper";
            role = "Controller";
            break;
        case 3:
            location = { 1209,848 };
            name = "Omen";
            role = "Controller";
            break;
        case 4:
            location = { 791,924 };
            name = "Astra";
            role = "Controller";
            break;
        case 5:
            location = { 881,844 };
            name = "Harbor";
            role = "Controller";
            break;
        case 6:
            location = { 712,915 };
            name = "Sova";
            role = "Initiator";
            break;
        case 7:
            location = { 873,925 };
            name = "Breach";
            role = "Initiator";
            break;
        case 8:
            location = { 792,1008 };
            name = "Skye";
            role = "Initiator";
            break;
        case 9:
            location = { 1294,927 };
            name = "KAY/O";
            role = "Initiator";
            break;
        case 10:
            location = { 798,837 };
            name = "Fade";
            role = "Initiator";
            break;
        case 11:
            location = { 1127,927 };
            name = "Gekko";
            role = "Initiator";
            break;
        case 12:
            location = { 1044,842 };
            name = "Killjoy";
            role = "Sentinel";
            break;
        case 13:
            location = { 1042,925 };
            name = "Cypher";
            role = "Sentinel";
            break;
        case 14:
            location = { 627,918 };
            name = "Sage";
            role = "Sentinel";
            break;
        case 15:
            location = { 959,924 };
            name = "Chamber";
            role = "Sentinel";
            break;
        case 16:
            location = { 709,841 };
            name = "Deadlock";
            role = "Sentinel";
            break;
        case 17:
            location = { 1294,843 };
            name = "Phoenix";
            role = "Duelist";
            break;
        case 18:
            location = { 963,841 };
            name = "Jett";
            role = "Duelist";
            break;
        case 19:
            location = { 709,1007 };
            name = "Reyna";
            role = "Duelist";
            break;
        case 20:
            location = { 622,1003 };
            name = "Raze";
            role = "Duelist";
            break;
        case 21:
            location = { 960,1005 };
            name = "Yoru";
            role = "Duelist";
            break;
        case 22:
            location = { 1137,840 };
            name = "Neon";
            role = "Duelist";
            break;
        case 23:
            location = { 1213,926 };
            name = "Iso";
            role = "Duelist";
        default:
            break;
        }
        return new Agent(location, name, role, id);
    }
    static void printLine() {
        for (int i = 0; i < 60; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }
    static void listIds() {
        std::cout << "There are a total of " << AGENT_COUNT << " Agents" << std::endl;
        printLine();
        std::cout << "ID   <=>   NAME   <=>   ROLE   <=>   LOCATION (X|Y)" << std::endl;
        printLine();
        for (int i = 1; i < (AGENT_COUNT + 1);i++) { //really starting at 1
            Agent* temp = resolveAgent(i);
            std::cout<< temp->getID() <<"  <=>  "<< temp->getName() <<"  <=>  "<< temp->getRole() <<"  <=>  ("<< temp->getLocation().x <<"|"<< temp->getLocation().y << ")" << std::endl;
        }
        printLine();
    }
    int getAgentCount() {
        return this->AGENT_COUNT;
    }
};
static bool checkCurrentState(std::vector<int> key) {
    int sum = 0;
    for (int i = 0; i < key.size(); i++) {
        sum += (bool)GetAsyncKeyState(key[i]);
    }
    //sum is length if 1 1 1
    return sum == key.size();
}

void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int cycles = 0;
static void select(Agent* agent, POINT SELECT, int delay) {
    POINT CHARACTER = agent->getLocation();
    LPPOINT pCursor = new POINT;
    if (pCursor != NULL) {
        GetCursorPos(pCursor);
        auto p = *pCursor;

        SetCursorPos(CHARACTER.x, CHARACTER.y); //move to character

        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); //perform doubleclick
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        sleep(delay);
        SetCursorPos(SELECT.x, SELECT.y); //move to character
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); //perform doubleclick
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        sleep(delay);
        cycles++;
    }
    delete(pCursor);
}
void showHelp(char* args) {
    std::cout << "Help:"<<std::endl;
    Agents::listIds();
    std::cerr << "Usage: " << args << " <agent_id> <delay in milliseconds> \nfor more have a look at readme.md (;" << std::endl;
}
 // const POINT NEON = { 1146, 830 };
const POINT SELECT = { 954, 712 };
std::vector<std::vector<int>> keys = { {0x53}, {0x50} }; //S P
bool is_selecting =  false;
int main(int argc, char* argv[]){
    if (argc != 3) { //check if 3 parameter
        showHelp(argv[0]);
        return 1;
    }
    int delay = std::atoi(argv[2]); //cast the delay to int
    if (delay < 0 || delay > 50) { //a delay higher as 50 is not recommended
        if (delay < 50) {
            std::cerr << "A delay higher as 50ms is not reccommended." << std::endl;
        }else{
            std::cerr << "Invalid milliseconds value." << std::endl;
        }
        return 1;
    }
    int agent_id = std::atoi(argv[1]);
    if (agent_id > Agents::AGENT_COUNT) { //if bigger => random select
        srand(time(0));
        agent_id = (rand()%23) + 1;
        std::cout << "Randomly selected: " << Agents::resolveAgent(agent_id)->getName() << std::endl;
    }
    Agent* agent = Agents::resolveAgent(agent_id);
    std::string agent_name = agent->getName();
    std::cout << "started instalock on "<< agent_name <<" with a " << delay << "ms delay"<<std::endl;
    long long int max_cycles = 9999999999999999999;
    while (max_cycles!=0) {
        if (checkCurrentState(keys[0])&& !is_selecting) { // S is pressed
            is_selecting = true;
        }
        else if (checkCurrentState(keys[1])) { // P is pressed
            is_selecting = false;
            std::cout << "bye bye :) \n I selected "<< agent->getName() <<" with "<< cycles <<" cycles\nGO GO GO\nNow go play and carry your team!" << std::endl;
            sleep(3000);
            exit(0);
        }
        if (is_selecting) {
            select(agent,SELECT,delay); //delay in ms
        }
        max_cycles--;
    }
    return 0;
}