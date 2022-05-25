#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>


namespace ariel{
    //default class - string
    template <class T = std::string>
    class OrgChart{
        struct Member{
            T title;
            Member* next;
            std::vector<Member*> employees;
            Member(T val) : title(val), next(nullptr), employees() {}
        };
        Member* root;
        public:
            OrgChart(): root(nullptr){}
            OrgChart& add_root(T new_root){
                if (root == nullptr){
                    root = new Member(new_root);
                }
                else{
                    root->title = new_root;
                }
                return *this;
            }

            OrgChart& add_sub(T sup, T sub){
                if (root == nullptr){
                    throw std::invalid_argument("cant find superior");
                }
                std::queue<Member*> find_sup_queue;
                find_sup_queue.push(root);
                while(find_sup_queue.size() > 0){
                    if (find_sup_queue.front()->title == sup){
                        Member* sub_member = new Member(sub);
                        find_sup_queue.front()->employees.push_back(sub_member);
                        while(!find_sup_queue.empty()){
                            find_sup_queue.pop();
                        }
                        return *this;
                    }
                    Member* curr_member = find_sup_queue.front();
                    find_sup_queue.pop();
                    for (size_t i = 0; i<curr_member->employees.size();i++){
                        find_sup_queue.push(curr_member->employees[i]);
                    }
                }
                throw std::invalid_argument("cant find superior");
            }

            friend std::ostream &operator<<(std::ostream& os , const OrgChart &chart){
                if (chart.root == nullptr) {
                    return os;
                }
                std::queue<Member*> osq;
                osq.push(chart.root);
                while (!osq.empty()) {
                    Member* curr = osq.front();
                    osq.pop();
                    if (curr->employees.size() > 0){
                        std::cout << " " << curr->title << "->" << std::endl;
                    }
                    for (size_t i =0; i<curr->employees.size(); i++){
                        osq.push(curr->employees[i]);
                        std::cout << curr->employees[i]->title << " ";
                    }
                    if (curr->employees.size() > 0){
                        std::cout << std::endl;
                    }
                }
                return os;
            }

            class chart_itertaor{
                private:
                    Member* curr_member;
                public:
                	chart_itertaor(Member* curr)
                        : curr_member(curr)  {}

                    T& operator*() const {
                        return curr_member->title;
                    }

                    T* operator->() const {
                        return &(curr_member->title);
                    }

                    chart_itertaor& operator++() {
                        curr_member = curr_member->next;
                        return *this;
                    }

                    Member* operator&(){
                        return curr_member;
                    }

                    bool operator!=(const chart_itertaor& other) const{
                        return curr_member != other.curr_member;
                    }

                    bool operator==(const chart_itertaor& other) const {
                        return curr_member == other.curr_member;
                    }
            };

            void root_null_throw(){
                if (root == nullptr){
                    throw std::invalid_argument("empty chart");
                }
            }

            chart_itertaor begin_level_order() {
                root_null_throw();
                std::vector<Member*> iterator_vec;
                size_t i = 0;
                iterator_vec.push_back(root);
                while (i<iterator_vec.size()){
                    for (size_t j = 0; j<iterator_vec[i]->employees.size();j++){
                        iterator_vec.push_back(iterator_vec[i]->employees[j]);
                    }
                    i++;
                }
                for (size_t i =0; i < iterator_vec.size(); i++){
                    iterator_vec[i]->next = (i!=iterator_vec.size()-1) ? iterator_vec[i+1] : nullptr;
                }
                return chart_itertaor(iterator_vec[0]);
            }

            chart_itertaor end_level_order() {
                root_null_throw();
                return chart_itertaor(nullptr);
            }

            chart_itertaor begin_reverse_order() {
                root_null_throw();
                std::queue<Member*> queuetostack;
                std::stack<Member*> rlostack;
                queuetostack.push(root);
                while(!queuetostack.empty()){
                    Member* temp = queuetostack.front();
                    queuetostack.pop();
                    rlostack.push(temp);
                    for (size_t i = temp->employees.size(); i>0;i--){
                        queuetostack.push(temp->employees[i-1]);
                    }
                }
                Member* first = rlostack.top();
                rlostack.pop();
                Member* curr = first;
                while(!rlostack.empty()){
                    Member* temp = rlostack.top();
                    rlostack.pop();
                    curr->next = temp;
                    curr = temp;
                }
                curr->next = nullptr;
                return chart_itertaor(first);
            }

            chart_itertaor reverse_order() {
                root_null_throw();
                return chart_itertaor(nullptr);
            }

            void fill_vector_preorder(Member* curr){
                if (curr!=nullptr){
                    povector.push_back(curr);
                    for (size_t i = 0; i < curr->employees.size(); i++){
                        fill_vector_preorder(curr->employees[i]);
                    }
                }
            }

            chart_itertaor begin_preorder() {
                root_null_throw();
                this->fill_vector_preorder(root);
                for (size_t i = 0; i<povector.size(); i++){
                    povector[i]->next = (i!=povector.size()-1) ? povector[i+1] : nullptr;
                }
                Member* first = povector[0];
                povector.clear();
                return chart_itertaor(first);
            }

            chart_itertaor end_preorder() {
                root_null_throw();
                return chart_itertaor(nullptr);
            }

            chart_itertaor begin() {
                return this->begin_level_order();
            }

            chart_itertaor end() {
                return end_level_order();
            }

            ~OrgChart(){
                if (root == nullptr){
                    return;
                }
                std::queue<Member*> delete_queue;
                delete_queue.push(root);
                while (!delete_queue.empty()){
                    Member* curr_delete = delete_queue.front();
                    delete_queue.pop();
                    for (size_t j = 0; j<curr_delete->employees.size();j++){
                        delete_queue.push(curr_delete->employees[j]);
                    }
                    delete curr_delete;
                }
            }







            //make tidy functions
            OrgChart (const OrgChart& copy_chart){}
            OrgChart& operator=(const OrgChart& copy_chart)=delete;
            OrgChart(OrgChart && move_chart)noexcept{};
            OrgChart& operator=(OrgChart&& move_chart)=delete;
            private:
                std::vector<Member*> povector;
    };
}