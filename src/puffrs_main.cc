// Copyright 2017 John T. Foster

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <iostream>

#include "Teuchos_GlobalMPISession.hpp"
#include "Xpetra_DefaultPlatform.hpp"

#include "puffrs_factory.h"
#include "puffrs_version.h"

int main(int argc, char* argv[]) {
    // Initialize MPI
    Teuchos::GlobalMPISession mpi_session(&argc, &argv, NULL);

    auto kComm = Xpetra::DefaultPlatform::getDefaultPlatform().getComm();

    const auto kRank = kComm->getRank();
    const auto kNumberOfProcessors = kComm->getSize();

    // Banner
    if (kRank == 0) {
        std::cout << "\n-- puffrs v " << Puffrs_GIT_COMMIT_HASH << std::endl;
        if (kNumberOfProcessors > 1)
            std::cout << "MPI initialized on " << kNumberOfProcessors
                      << " processors.\n"
                      << std::endl;
    }

    if (argc != 2) {
        if (kRank == 0)
            std::cout << "Usage:  puffrs <input.yml>\n" << std::endl;
        return 1;
    }

    // Get filename string from command line
    const auto kYamlFileName(argv[1]);

    // Create factory object to produce main puffrs object
    puffrs::PuffrsFactory puffrs_factory;
    // Create puffrs object
    auto puffrs = puffrs_factory.Create(kYamlFileName, kComm);

    return 0;
}
