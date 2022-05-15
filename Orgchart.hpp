#pragma once
#include <iostream>
#include <vector>

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
                for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it){
                    if((*it) == sup){
                        Member* curr_member = (&it);
                        Member* new_member = new Member(sub);
                        curr_member->employees.push_back(new_member);
                        if (curr_member->superior->employees.size()-2 >= 0){
                            curr_member->superior->employees[curr_member->superior->employees.size()-2]->brother = new_member;
                        }
                        return *this;
                    }
                }
                throw std::invalid_argument("cant find sup");;
            }

            friend std::ostream &operator<<(std::ostream& os , const OrgChart &chart){
                std::cout << "hello" << std::endl;
                return os;
            }

            class chart_itertaor{
                private:
                    Member* curr_member;
                public:
                	chart_itertaor(Member* ptr = nullptr)
                        : curr_member(ptr) {}

                    T& operator*() const {
                        return curr_member->title;
                    }

                    T* operator->() const {
                        return &(curr_member->title);
                    }

                    chart_itertaor& operator++() {
                        if (curr_member->employees.size() > 0){
                            curr_member = curr_member->employees[0];
                            return *this;
                        }
                        curr_member = curr_member->superior;
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

        public:
            chart_itertaor begin_level_order() {
                
                return chart_itertaor{root};
            }

            chart_itertaor end_level_order() {
                return chart_itertaor{nullptr};
            }

            chart_itertaor begin_reverse_order() {
                return chart_itertaor{root};
            }

            chart_itertaor reverse_order() {
                return chart_itertaor{nullptr};
            }

            chart_itertaor begin_preorder() {
                return chart_itertaor{root};
            }

            chart_itertaor end_preorder() {
                return chart_itertaor{nullptr};
            }

            chart_itertaor begin() {
                return chart_itertaor{root};
            }

            chart_itertaor end() {
                return chart_itertaor{nullptr};
            }
    };
}