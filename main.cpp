#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <unordered_set>


struct node{
    std::string state;
    node * prevState = nullptr;
    node * uchild = nullptr;
    node * lchild = nullptr;
    node * dchild = nullptr;
    node * rchild = nullptr;
    int cost = 0;
    int heuristic = 0;
    int priority;
    node(std::string state, node* prevState, int priority) : state(state), prevState(prevState), priority(priority){
    }
    node(std::string state, node* prevState) : state(state), prevState(prevState){
    }

    // bool operator< (const node& compared) const{
    //     return priority < compared.priority;
    // }

    bool operator== (const node& compared) const{
        return state == compared.state;
    }

    ~node(){
        delete uchild;
        delete lchild;
        delete dchild;
        delete rchild;
    }
};

struct comparison{
    bool operator()(const node* first, const node* second) const{
        return first->priority > second->priority;
    }
};


void queueingFunct(std::priority_queue<node*, std::vector<node*>, comparison>& nodes, int type, std::unordered_set<std::string>& checker, node* currnode, int& counter){
    std::string temp;
    char holder;
    int index = currnode->state.find("0");
    counter++;
    if(index - 3 >= 0){
        temp = currnode->state;
        holder = temp.at(index);
        temp.at(index) = temp.at(index-3);
        temp.at(index-3) = holder;
        currnode->uchild = new node(temp, currnode);
        currnode->uchild->cost = currnode->cost + 1;
    }
    if(index + 1 < 9 && index != 2 && index != 5){
        temp = currnode->state;
        holder = temp.at(index);
        temp.at(index) = temp.at(index+1);
        temp.at(index+1) = holder;
        currnode->rchild = new node(temp, currnode);
        currnode->rchild->cost = currnode->cost + 1;
    }
    if(index + 3 < 9){
        temp = currnode->state;
        holder = temp.at(index);
        temp.at(index) = temp.at(index+3);
        temp.at(index+3) = holder;
        currnode->dchild = new node(temp, currnode);
        currnode->dchild->cost = currnode->cost + 1;
    }
    if(index - 1 >= 0 && index != 3 && index != 6){
        temp = currnode->state;
        holder = temp.at(index);
        temp.at(index) = temp.at(index-1);
        temp.at(index-1) = holder;
        currnode->lchild = new node(temp, currnode);
        currnode->lchild->cost = currnode->cost + 1;
    }


    if(type == 1){
        if(currnode->uchild != nullptr){
            currnode->uchild->priority = currnode->uchild->cost;
        }
        if(currnode->lchild != nullptr){
            currnode->lchild->priority = currnode->lchild->cost;
        }
        if(currnode->dchild != nullptr){
            currnode->dchild->priority = currnode->dchild->cost;
        }
        if(currnode->rchild != nullptr){
            currnode->rchild->priority = currnode->rchild->cost;
        }
    }
    else if(type == 2){
        if(currnode->uchild != nullptr){
            int counter = 0;
            int checkingValue;
            for(int i = 0; i < 9; i++){
                checkingValue = currnode->uchild->state.at(i) - '0';
                if(checkingValue != 0 && checkingValue != i + 1){
                    counter++;
                }
            }
            currnode->uchild->heuristic = counter;
            currnode->uchild->priority = currnode->uchild->cost + counter;
        }
        if(currnode->lchild != nullptr){
            int counter = 0;
            int checkingValue;
            for(int i = 0; i < 9; i++){
                checkingValue = currnode->lchild->state.at(i) - '0';
                if(checkingValue != 0 && checkingValue != i + 1){
                    counter++;
                }
            }
            currnode->lchild->heuristic = counter;
            currnode->lchild->priority = currnode->lchild->cost + counter;
        }
        if(currnode->dchild != nullptr){
            int counter = 0;
            int checkingValue;
            for(int i = 0; i < 9; i++){
                checkingValue = currnode->dchild->state.at(i) - '0';
                if(checkingValue != 0 && checkingValue != i + 1){
                    counter++;
                }
            }
            currnode->dchild->heuristic = counter;
            currnode->dchild->priority = currnode->dchild->cost + counter;
        }
        if(currnode->rchild != nullptr){
            int counter = 0;
            int checkingValue;
            for(int i = 0; i < 9; i++){
                checkingValue = currnode->rchild->state.at(i) - '0';
                if(checkingValue != 0 && checkingValue != i + 1){
                    counter++;
                }
            }
            currnode->rchild->heuristic = counter;
            currnode->rchild->priority = currnode->rchild->cost + counter;
        }
    }
    else{
        if(currnode->uchild != nullptr){
            int counter = 0;
            int checkingValue;
            for(int i = 0; i < 9; i++){
                checkingValue = currnode->uchild->state.at(i) - '0';
                if(checkingValue != 0 && checkingValue != i + 1){
                    int tempVal = checkingValue - 1;
                    int rowT = tempVal / 3;
                    int rowC = i / 3;
                    int colT = tempVal % 3;
                    int colC = i % 3;
                    counter += abs(rowT - rowC) + abs(colT - colC);
                }
            }
            currnode->uchild->heuristic = counter;
            currnode->uchild->priority = currnode->uchild->cost + counter;
        }
        if(currnode->lchild != nullptr){
            int counter = 0;
            int checkingValue;
            for(int i = 0; i < 9; i++){
                checkingValue = currnode->lchild->state.at(i) - '0';
                if(checkingValue != 0 && checkingValue != i + 1){
                    int tempVal = checkingValue - 1;
                    int rowT = tempVal / 3;
                    int rowC = i / 3;
                    int colT = tempVal % 3;
                    int colC = i % 3;
                    counter += abs(rowT - rowC) + abs(colT - colC);
                }
            }
            currnode->lchild->heuristic = counter;
            currnode->lchild->priority = currnode->lchild->cost + counter;
        }
        if(currnode->dchild != nullptr){
            int counter = 0;
            int checkingValue;
            for(int i = 0; i < 9; i++){
                checkingValue = currnode->dchild->state.at(i) - '0';
                if(checkingValue != 0 && checkingValue != i + 1){
                    int tempVal = checkingValue - 1;
                    int rowT = tempVal / 3;
                    int rowC = i / 3;
                    int colT = tempVal % 3;
                    int colC = i % 3;
                    counter += abs(rowT - rowC) + abs(colT - colC);
                }
            }
            currnode->dchild->heuristic = counter;
            currnode->dchild->priority = currnode->dchild->cost + counter;
        }
        if(currnode->rchild != nullptr){
            int counter = 0;
            int checkingValue;
            for(int i = 0; i < 9; i++){
                checkingValue = currnode->rchild->state.at(i) - '0';
                if(checkingValue != 0 && checkingValue != i + 1){
                    int tempVal = checkingValue - 1;
                    int rowT = tempVal / 3;
                    int rowC = i / 3;
                    int colT = tempVal % 3;
                    int colC = i % 3;
                    counter += abs(rowT - rowC) + abs(colT - colC);
                }
            }
            currnode->rchild->heuristic = counter;
            currnode->rchild->priority = currnode->rchild->cost + counter;
        }
    }

    if(currnode->uchild != nullptr){
        nodes.push(currnode->uchild);
    }
    if(currnode->lchild != nullptr){
        nodes.push(currnode->lchild);
    }
    if(currnode->dchild != nullptr){
        nodes.push(currnode->dchild);
    }
    if(currnode->rchild != nullptr){
        nodes.push(currnode->rchild);
    }
}

node* general_search(std::string initState, std::string goalState, int type, std::unordered_set<std::string>& checker, int& counter, int& queuemaxsize){
    if(type > 4 || type < 1){
        std::cout << "Invalid type" << std::endl;
        return nullptr;
    }
    std::priority_queue<node*, std::vector<node*>, comparison> nodes;
    node* initNode = new node(initState, nullptr, 0);
    nodes.push(initNode);
    node* checkNode = nullptr;
    while(1){
        if(nodes.empty()){
            return nullptr;
        }
        checkNode = nodes.top();
        nodes.pop();
        if(checker.count(checkNode->state) == 1){
            continue;
        }
        checker.insert(checkNode->state);
        if(goalState == checkNode->state){
            return checkNode;
        }
        else{
            queueingFunct(nodes, type, checker, checkNode, counter);
            if(nodes.size() > queuemaxsize){
                queuemaxsize = nodes.size();
            }
        }
    }

}


int main(){
    std::string initial_state = "";
    std::cout << "This is an 8 Tile Puzzle solver.  Please enter in your values.  0 will represent the empty tile.  For example, the string 123456780 is" << std::endl;
    std::cout << "1 2 3" << std::endl;
    std::cout << "4 5 6" << std::endl;
    std::cout << "7 8 0" << std::endl;
    std::getline(std::cin, initial_state);
    int type = 0;
    std::cout << "Please choose a type using a number: 1 for Uniform Cost, 2 for Misplaced Tile, 3 for Manhattan Distance.  Press enter when finished" << std::endl;
    std::cin >> type;
    std::string initState = initial_state; 
    std::string goalState = "123456780";
    node* solnode = nullptr;
    std::unordered_set<std::string> checker;
    int counter = 0;
    int queuemaxsize = 0;
    node* found;
    solnode = general_search(initState, goalState, type, checker, counter, queuemaxsize);
    if(solnode == nullptr){
        std::cout << "No path possible" << std::endl;
    }
    std::vector<node*> path;
    node* pathfinder = solnode;
    while(pathfinder != nullptr){
        path.insert(path.begin(), pathfinder);
        pathfinder = pathfinder->prevState;
    }
    for(int i = 0; i < path.size(); i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                std::cout << path.at(i)->state.at((3 * j) + k) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "The cost of the at this state is " << path.at(i)->cost << " and the heuristic value is " << path.at(i)->heuristic << std::endl;
        if(i != path.size() - 1){
            std::string corrMove = "";
            if(path.at(i+1) == path.at(i)->uchild){
                corrMove = "up";
            }
            else if(path.at(i+1) == path.at(i)->rchild){
                corrMove = "right";
            }
            else if(path.at(i+1) == path.at(i)->dchild){
                corrMove = "down";
            }
            else if(path.at(i+1) == path.at(i)->lchild){
                corrMove = "left";
            }
            else{
                corrMove = "wrong behavior";
            }
            std::cout << "The best move to take is to move the tile " << corrMove << std::endl;
            std::cout << std::endl;
        }
        else{
            std::cout << "Goal State" << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "The depth of the problem is " << path.size() - 1 << std::endl;
    std::cout << "The number of nodes expanded is " << counter << std::endl;
    std::cout << "The max queue size is " << queuemaxsize << std::endl;

    return 0;
}

