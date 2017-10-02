/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Microsoft Corporation. All rights reserved.
 *  Licensed under the MIT License. See License.txt in the project root for license information.
 *--------------------------------------------------------------------------------------------*/

#ifndef EDCORE_BUFFER_H_
#define EDCORE_BUFFER_H_

#include "buffer-piece.h"

#include <memory>
#include <vector>

namespace edcore
{

struct BufferNode2 {
    size_t length;
    size_t newLineCount;
};
typedef struct BufferNode2 BufferNode2;

struct BufferCursor2
{
    size_t offset;
    size_t leafIndex;
    size_t leafStartOffset;
};
typedef struct BufferCursor2 BufferCursor2;

class Buffer
{
public:
    Buffer(vector<BufferPiece*> &pieces);
    ~Buffer();
    size_t length() const { return nodes_[1].length; }
    size_t lineCount() const { return nodes_[1].newLineCount + 1; }
    void print(ostream &os, size_t index, size_t indent);

    bool findOffset2(size_t offset, BufferCursor2 &result);

    bool findLine2(size_t lineNumber, BufferCursor2 &start, BufferCursor2 &end);

    void extractString2(BufferCursor2 start, size_t len, uint16_t *dest);

  private:
    
    BufferNode2 *nodes_;
    size_t nodesCount_;
    
    BufferPiece **leafs_;
    size_t leafsCount_;
    size_t leafsStart_;
    size_t leafsEnd_;

    bool _findLineStart(size_t &lineIndex, BufferCursor2 &result);
    void _findLineEnd(size_t leafIndex, size_t leafStartOffset, size_t innerLineIndex, BufferCursor2 &result);

};
}

#endif
