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
            Member *brother;
            std::vector<Member*> employees;
            Member(T val) : title(val), superior(nullptr), brother(nullptr), employees() {}
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
                queue<Member*> find_sub;
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
                return *this;
            }

            friend std::ostream &operator<<(std::ostream& os , const OrgChart &chart){
                std::cout << "hello" << std::endl;
                return os;
            }

            class level_order_itertaor{
                private:
                    Member* curr_member;
                    queue<Member*> loqueue;
                public:
                	level_order_itertaor(Member* ptr)
                        : curr_member(ptr)  {loqueue.push(ptr);}

                    T& operator*() const {
                        return curr_member->title;
                    }

                    T* operator->() const {
                        return &(curr_member->title);
                    }

                    level_order_itertaor& operator++() {
                        for (size_t i=0; i<curr_member->employees.size(); i++){
                            loqueue.push(curr_member->employees[i]);
                        }
                        if (loqueue.size() == 1){
                            loqueue.pop();
                            curr_member = nullptr;
                            return *this;
                        }
                        loqueue.pop();
                        curr_member = loqueue.front();
                        return *this;
                    }

                    Member* operator&(){
                        return curr_member;
                    }

                    bool operator!=(const level_order_itertaor& other) const{
                        return curr_member != other.curr_member;
                    }

                    bool operator==(const level_order_itertaor& other) const {
                        return curr_member == other.curr_member;
                    }
            };

            class reverse_level_order_itertaor{
                private:
                    Member* curr_member;
                    stack<Member*> rlostack;
                public:
                	reverse_level_order_itertaor(Member* ptr)
                        : curr_member(ptr) {
                            if (ptr!=nullptr){
                                queue<Member*> tostack;
                                tostack.push(ptr);
                                while(!tostack.empty()){
                                    Member* temp = tostack.front();
                                    tostack.pop();
                                    rlostack.push(temp);
                                    for (size_t i = 0; i<temp->employees.size();i++){
                                        tostack.push(temp->employees[i]);
                                    }
                                }
                                curr_member = rlostack.top();
                                rlostack.pop();
                            }
                        }

                    T& operator*() const {
                        return curr_member->title;
                    }

                    T* operator->() const {
                        return &(curr_member->title);
                    }

                    reverse_level_order_itertaor& operator++() {
                        if (rlostack.size()>0){
                            curr_member = rlostack.top();
                            rlostack.pop();
                            return *this;
                        }
                        curr_member = nullptr;
                        return *this;
                    }

                    Member* operator&(){
                        return curr_member;
                    }

                    bool operator!=(const reverse_level_order_itertaor& other) const{
                        return curr_member != other.curr_member;
                    }

                    bool operator==(const reverse_level_order_itertaor& other) const {
                        return curr_member == other.curr_member;
                    }
            };

        public:
            level_order_itertaor begin_level_order() {
                return level_order_itertaor(root);
            }

            level_order_itertaor end_level_order() {
                return level_order_itertaor(nullptr);
            }

            reverse_level_order_itertaor begin_reverse_order() {
                return reverse_level_order_itertaor(root);
            }

            reverse_level_order_itertaor reverse_order() {
                return reverse_level_order_itertaor(nullptr);
            }

            level_order_itertaor begin_preorder() {
                return level_order_itertaor(root);
            }

            level_order_itertaor end_preorder() {
                return level_order_itertaor(nullptr);
            }

            level_order_itertaor begin() {
                return level_order_itertaor(root);
            }

            level_order_itertaor end() {
                return level_order_itertaor(nullptr);
            }
    };
}