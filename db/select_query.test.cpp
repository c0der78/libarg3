#include <igloo/igloo.h>
#include "base_record.h"
#include "db.test.h"

using namespace igloo;

using namespace std;

using namespace arg3::db;

Context(select_query_test)
{
    static void SetUpContext()
    {
        testdb.setup();

        user user1;

        user1.set("id", 1);
        user1.set("first_name", "Bryan");
        user1.set("last_name", "Jenkins");

        user1.save();


        user user2;

        user2.set("id", 3);

        user2.set("first_name", "Bob");
        user2.set("last_name", "Smith");

        user2.save();
    }

    static void TearDownContext()
    {
        testdb.teardown();
    }

    Spec(where_test)
    {
        try
        {
            auto query = select_query(&testdb, "users");

            query.where("first_name=? OR last_name=?");

            query.bind(1, "Bryan");
            query.bind(2, "Jenkins");

            auto results = query.execute();

            auto row = results.begin();

            Assert::That(row != results.end(), Equals(true));

            string lastName = row->column_value("last_name").to_string();

            Assert::That(lastName, Equals("Jenkins"));
        }
        catch (const database_exception &e)
        {
            cout << testdb.lastError() << endl;
            throw e;
        }
    }

    Spec(executeScalar)
    {
        vector<string> columns = { "first_name"};

        auto query = select_query(&testdb, "users", columns);

        query.where("first_name=?");

        query.bind(1, "Bryan");

        string value = query.executeScalar<string>();

        Assert::That(value, Equals("Bryan"));
    }


    Spec(binding_test)
    {
        select_query query(&testdb, "users");

        // sneaky, bind first, should be able to handle it
        query.bind(1, "Bryan");

        query.bind(2, "Jenkins");

        query.where("first_name=? and last_name=?");

        auto rs = query.execute();

        Assert::That(rs.is_valid(), Equals(true));

        auto u = rs.begin()->column_value("first_name");

        Assert::That(u.to_string(), Equals("Bryan"));
    }

};
