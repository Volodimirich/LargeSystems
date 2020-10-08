#include <iostream> 

#include <com/sun/star/frame/XFrame.hpp>

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextTable.hpp>
#include <com/sun/star/text/XTextTablesSupplier.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/XTableRows.hpp>
#include <com/sun/star/table/XTableColumns.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/table/XTable.hpp>


using namespace com::sun::star::uno;
using namespace com::sun::star::frame;
using namespace com::sun::star::text;
using namespace com::sun::star::table;
using namespace com::sun::star::container;

using ::rtl::OUString;
using ::rtl::OUStringToOString;
using ::rtl::OString;


size_t GetMaxSize(Reference<XTextTable> table) {
    auto rows = table->getRows();
    Reference<XIndexAccess> rows_indexes(rows, UNO_QUERY);
    
    auto columns = table->getColumns();
    Reference<XIndexAccess> columns_indexes(columns, UNO_QUERY);

    auto rows_amount = rows_indexes->getCount();
    auto columns_amount = columns_indexes->getCount();
    
    return rows_amount < columns_amount ? rows_amount : columns_amount;
}

void CellSwap(Reference<XCell> first_cell, Reference<XCell> second_cell) {
    Reference<XText> first_cell_data(first_cell, UNO_QUERY);
    Reference<XText> second_cell_data(second_cell, UNO_QUERY);
    auto tmp_cell_string = first_cell_data->getString();
        
    first_cell_data->setString(second_cell_data->getString());
    second_cell_data->setString(tmp_cell_string);
}


void TableTransposition(Reference<XTextTable> table) {
    size_t max_len = GetMaxSize(table);
    Reference<XCellRange> range(table, UNO_QUERY);
    
    for (uint32_t column = 0; column < max_len; column++)
        for (uint32_t row = column; row < max_len; row++)
            CellSwap(range->getCellByPosition(column, row), range->getCellByPosition(row, column));
        
}

void FullTableTransposition(Reference<XFrame> frame) {
    Reference<XTextDocument> document(frame->getController()->getModel(), UNO_QUERY);
    Reference<XTextTablesSupplier> table_helper(document, UNO_QUERY);

    auto text_tables = table_helper->getTextTables();
    auto tables_names = text_tables->getElementNames();
    
    for (size_t i = 0; i < tables_names.getLength(); i++) {
        Reference<XTextTable> table(text_tables->getByName(tables_names[i]), UNO_QUERY);
        TableTransposition(table);
    }
}
