#ifndef ARG3_DB_WHERE_CLAUSE_H_
#define ARG3_DB_WHERE_CLAUSE_H_

#include <vector>
#include <string>

using namespace std;

namespace arg3
{
    namespace db
    {
        class where_clause
        {
        private:
            vector<where_clause> and_;
            vector<where_clause> or_;
            string value_;

        public:
            where_clause();
            explicit where_clause(const string &value);
            where_clause(const where_clause &other);
            where_clause(where_clause &&other);
            where_clause &operator=(const where_clause &other);
            where_clause &operator=(where_clause &&other);

            virtual ~where_clause();

            string to_string() const;

            explicit operator string();

            where_clause &operator&&(const string &value);
            where_clause &operator&&(const where_clause &value);
            where_clause &operator||(const where_clause &value);
            where_clause &operator||(const string &value);

            bool empty() const;
        };



        inline where_clause Q(const char *str)
        {
            return where_clause(str);
        }

    }
}

#endif
