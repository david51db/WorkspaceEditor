//
// Created by David on 5/18/2026.
//

#include "DocumentFactory.h"

#include "TextDocument.h"
#include "ToDoDocument.h"
using namespace std;


std::unique_ptr<Document> DocumentFactory::create(DocumentType type) {
    switch (type) {
        case DocumentType::Text: return make_unique<TextDocument>();
        case DocumentType::ToDo: return make_unique<ToDoDocument>();
    }
}
