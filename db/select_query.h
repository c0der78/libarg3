/*!
 * @copyright ryan jennings (arg3.com), 2013 under LGPL
 */
#ifndef _ARG3_DB_SELECT_QUERY_H_
#define _ARG3_DB_SELECT_QUERY_H_

#include "base_query.h"
#include "resultset.h"
#include "where_clause.h"

namespace arg3
{
    namespace db
    {
        class sqldb;

        class select_query : public base_query
        {
        public:

            friend class resultset;
        private:
            where_clause where_;
            string limit_;
            string orderBy_;
            string groupBy_;

            vector<string> columns_;
        public:

            select_query(sqldb *db, const string &tableName, const vector<string> &columns);

            select_query(sqldb *db, const string &tableName);

            select_query(const select_query &other);

            select_query(select_query &&other);

            virtual ~select_query();

            select_query &operator=(const select_query &other);

            select_query &operator=(select_query &&other);

            select_query &where(const where_clause &value);

            select_query &where(const string &value);

            select_query &limit(const string &value);

            select_query &orderBy(const string &value);

            select_query &groupBy(const string &value);

            string to_string() const;

            resultset execute();

            template<typename T>
            T executeScalar() {
                auto rs = execute();

                auto row = rs.begin();

                auto col = row->begin();

                return *col;
            }

        };

    }
}

#endif
