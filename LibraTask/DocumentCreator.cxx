#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>


#include <com/sun/star/text/XTextTable.hpp>
#include <com/sun/star/text/XTextTablesSupplier.hpp>
#include <com/sun/star/text/XTextContent.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/XTableRows.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/table/XTable.hpp>

#include <com/sun/star/frame/Desktop.hpp>


#include <string>
#include <cstdlib>
#include <ctime>

using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::frame;
using namespace com::sun::star::text;
using namespace com::sun::star::table;
using namespace com::sun::star::container;

using ::rtl::OUString;
using ::rtl::OUStringToOString;
using ::rtl::OString;


void TableFiller(Reference <XTextTable> &table, int num_of_col, int num_of_row) {
    Reference<XCellRange> range(table, UNO_QUERY);

    for (int col = 0; col < num_of_col; col++) {
        for (int row = 0; row < num_of_row; row++) {
            Reference<XText> cell_text(range->getCellByPosition(col, row), UNO_QUERY);
            std::string cell_value = "row_" + std::to_string(row) + " colm_" + std::to_string(col);

            cell_text->setString(OUString::createFromAscii(cell_value.c_str()));
        }
    }
}

void TableCreation(Reference <XMultiServiceFactory> &document, Reference <XText> &text) {
    
    size_t row_amount = std::rand() % 7 + 3;
    size_t column_amount = std::rand() % 5 + 3;

    Reference <XTextTable> table(document->createInstance(OUString::createFromAscii("com.sun.star.text.TextTable")), UNO_QUERY);
    table->initialize(row_amount, column_amount);
    auto text_range = text->getEnd();

    Reference <XTextContent> text_content(table, UNO_QUERY);
    text->insertTextContent(text_range, text_content, false);
    TableFiller(table, column_amount, row_amount);
}

void DocumentCreator(Reference<XComponentContext> xContext){
    std::srand(std::time(nullptr));

    size_t num_of_tables = std::rand() % 7 + 2;

    Reference<XMultiComponentFactory> xServiceManager = xContext->getServiceManager();
    Reference<XInterface> xDesktop = xServiceManager->createInstanceWithContext(OUString("com.sun.star.frame.Desktop"), xContext);

    Reference<XDesktop2> xDesktop2(xDesktop, UNO_QUERY);
    Reference<XComponent> xComponent = xDesktop2->loadComponentFromURL(OUString("private:factory/swriter"), // URL to the ods file
            OUString( "_blank" ), 0, Sequence < ::com::sun::star::beans::PropertyValue >());
    
    Reference <XTextDocument> text_doc(xComponent, UNO_QUERY);
    Reference <XText> text = text_doc->getText();
        
    Reference <XMultiServiceFactory> document(text_doc, UNO_QUERY);
    
    for (size_t i = 0; i < num_of_tables; i++) {
        auto text_cursor = text->createTextCursor();
        std::string table_name = "\nTable: " + std::to_string(i);
        
        text_cursor->gotoEnd(false);
        text_cursor->setString(OUString::createFromAscii(table_name.c_str()));
        TableCreation(document, text);
    }
}

