#include "secretNumberDilemma/csp/cspModel.h"

namespace secretNumberDilemma {
    CspModel::CspModel(std::vector<std::shared_ptr<Variable>> &variables) : variables(variables) {
        this->addConstraint(std::make_unique<AllDifferenceConstraint>(this->variables));
    }


    void CspModel::applyConstraints() const {
        bool modified;
        do {
            modified = false;
            for (const auto& constraint : this->constraints) {
                modified |= constraint->filterDomain();
            }
        } while (modified);
    }



    void CspModel::addConstraint(std::unique_ptr<Constraint> constraint) {
        this->constraints.push_back(std::move(constraint));
        this->applyConstraints();
    }

    std::vector<std::vector<uchar>> CspModel::simulateConstraint(Constraint *constraint) {
        // Create a copy of current domains (State)
        State state;
        state.reserve(this->variables.size());
        for (const auto& variable : this->variables) {
            state.push_back(variable->getDomain());
        }

        // Apply the new constraint on the simulated state
        constraint->simulateConstraint(state);

        // Apply all existing constraints iteratively until no more changes
        bool modified;
        do {
            modified = false;
            for (const auto& existingConstraint : this->constraints) {
                modified |= existingConstraint->simulateConstraint(state);
            }
        } while (modified);

        // Convert State (vector<set<uchar>>) to vector<vector<uchar>>
        std::vector<std::vector<uchar>> result;
        result.reserve(state.size());
        for (const auto& domain : state) {
            result.emplace_back(domain.begin(), domain.end());
        }

        return result;
    }

} // secretNumberDilemma