//
// Created by Tom on 18/11/2025.
//

#include "secretNumberDilemma/tests/variableTester.h"

namespace secretNumberDilemma {
    void VariableTester::runTests() {
        std::cout << "Running Variable tests..." << std::endl;
        VariableTester::testUniqueId();
        VariableTester::testInitialDomain();
        VariableTester::testRemoveValueFromDomain();
        std::cout << "ALL VARIABLE TESTS PASSED !\n" << std::endl;
    }

    void VariableTester::testUniqueId() {
        const Variable var1;
        const Variable var2;
        const Variable var3;

        assert(var1.getId() != var2.getId());
        assert(var1.getId() != var3.getId());
        assert(var2.getId() != var3.getId());

        std::cout << "\t-Unique ID test passed." <<  std::endl;
    }

    void VariableTester::testInitialDomain()  {
        const Variable var;

        const std::set<unsigned char> domain = var.getDomain();
        assert(domain.size() == 100);

        for (unsigned char i = 1; i <= 100; ++i) {
            assert(domain.contains(i));
        }

        std::cout << "\t-Initial Domain test passed." <<  std::endl;
    }

    void VariableTester::testRemoveValueFromDomain() {
        Variable var;

        bool res = var.removeValueFromDomain(50);
        assert(res);

        std::set<unsigned char> domain = var.getDomain();
        assert(domain.size() == 99);
        assert(!domain.contains(50));

        res = var.removeValueFromDomain(50);
        assert(!res);

        domain = var.getDomain();
        assert(domain.size() == 99);
        assert(!domain.contains(50));

        std::cout << "\t-Domain test passed." <<  std::endl;
    }

} // secretNumberDilemma