#ifndef DATABASEFACADEINTERFACE_H
#define DATABASEFACADEINTERFACE_H

#include <memory>

#include "../queryProcessor/DatabaseQueryProcessor.h"

class DatabaseFacade {
protected:
    std::shared_ptr<DatabaseQueryProcessor> m_processor;
    
public:
    DatabaseFacade(const std::shared_ptr<DatabaseQueryProcessor> &processor);
    
};

#endif // DATABASEFACADEINTERFACE_H
