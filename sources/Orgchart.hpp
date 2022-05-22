#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>


namespace ariel{
    template <class T = std::string>
    class OrgChart{
        struct Member{
            T title;
            Member *superior;
            std::vector<Member*> employees;
            Member(T val) : title(val), superior(nullptr), employees() {}
        };
        Member* root;
        public:
            OrgChart(): root(nullptr){}
            OrgChart& add_root(T new_root){
                if (root == nullptr){
                    root = new Member(new_root);
                    // TODO: pointer or not? 
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
                std::queue<Member*> find_sub;
                find_sub.push(root);
                while(find_sub.size() > 0){
                    if (find_sub.front()->title == sup){
                        Member* sub_member = new Member(sub);
                        find_sub.front()->employees.push_back(sub_member);
                        while(!find_sub.empty()){
                            find_sub.pop();
                        }
                        return *this;
                    }
                    Member* curr_member = find_sub.front();
                    find_sub.pop();
                    for (size_t i = 0; i<curr_member->employees.size();i++){
                        find_sub.push(curr_member->employees[i]);
                    }
                }
                throw std::invalid_argument("cant find superior");
            }

            friend std::ostream &operator<<(std::ostream& os , const OrgChart &chart){
                std::cout << "hello" << std::endl;
                return os;
            }

            class chart_itertaor{
                private:
                    Member* curr_member;
                    std::vector<Member*> chart_vec;
                    size_t i = 1;
                public:
                	chart_itertaor(std::vector<Member*> vec)
                        : curr_member(vec[0])  {chart_vec = vec;}

                    T& operator*() const {
                        return curr_member->title;
                    }

                    T* operator->() const {
                        return &(curr_member->title);
                    }

                    chart_itertaor& operator++() {
                        if (i < chart_vec.size()){
                            curr_member = chart_vec[i];
                            i++;
                            return *this;
                        }
                        curr_member = nullptr;
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

            chart_itertaor begin_level_order() {
                if (root == nullptr){
                    throw std::invalid_argument("empty chart");
                }
                std::vector<Member*> iterator_vec;
                size_t i = 0;
                iterator_vec.push_back(root);
                while (i<iterator_vec.size()){
                    for (size_t j = 0; j<iterator_vec[i]->employees.size();j++){
                        iterator_vec.push_back(iterator_vec[i]->employees[j]);
                    }
                    i++;
                }
                return chart_itertaor(iterator_vec);
            }

            chart_itertaor end_level_order() {
                if (root == nullptr){
                    throw std::invalid_argument("empty chart");
                }
                std::vector<Member*> iterator_vec;
                iterator_vec.push_back(nullptr);
                return chart_itertaor(iterator_vec);
            }

            chart_itertaor begin_reverse_order() {
                if (root == nullptr){
                    throw std::invalid_argument("empty chart");
                }
                std::vector<Member*> iterator_vec;
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
                while(!rlostack.empty()){
                    Member* temp = rlostack.top();
                    rlostack.pop();
                    iterator_vec.push_back(temp);
                }
                return chart_itertaor(iterator_vec);
            }

            chart_itertaor reverse_order() {
                if (root == nullptr){
                    throw std::invalid_argument("empty chart");
                }
                std::vector<Member*> iterator_vec;
                iterator_vec.push_back(nullptr);
                return chart_itertaor(iterator_vec);
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
                if (root == nullptr){
                    throw std::invalid_argument("empty chart");
                }
                std::vector<Member*> iterator_vec;
                this->fill_vector_preorder(root);
                for (size_t i = 0; i<povector.size(); i++){
                    iterator_vec.push_back(povector[i]);
                }
                povector.clear();
                return chart_itertaor(iterator_vec);
            }

            chart_itertaor end_preorder() {
                if (root == nullptr){
                    throw std::invalid_argument("empty chart");
                }
                std::vector<Member*> iterator_vec;
                iterator_vec.push_back(nullptr);
                return chart_itertaor(iterator_vec);
            }

            chart_itertaor begin() {
                return this->begin_level_order();
            }

            chart_itertaor end() {
                return end_level_order();
            }

            private:
                std::vector<Member*> povector;
    };
}