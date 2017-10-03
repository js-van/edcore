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

struct BufferNode
{
    size_t length;
    size_t newLineCount;
};
typedef struct BufferNode BufferNode;

struct BufferCursor
{
    size_t offset;
    size_t leafIndex;
    size_t leafStartOffset;
};
typedef struct BufferCursor BufferCursor;

class Buffer
{
  public:
    Buffer(vector<BufferPiece *> &pieces);
    ~Buffer();
    size_t length() const { return nodes_[1].length; }
    size_t lineCount() const { return nodes_[1].newLineCount + 1; }
    size_t memUsage() const;

    void print(ostream &os, size_t index, size_t indent);

    bool findOffset(size_t offset, BufferCursor &result);
    bool findLine(size_t lineNumber, BufferCursor &start, BufferCursor &end);
    void extractString(BufferCursor start, size_t len, uint16_t *dest);

    void deleteOneOffsetLen(size_t offset, size_t len);

  private:
    BufferNode *nodes_;
    size_t nodesCount_;

    BufferPiece **leafs_;
    size_t leafsCount_;
    size_t leafsStart_;
    size_t leafsEnd_;

    bool _findLineStart(size_t &lineIndex, BufferCursor &result);
    void _findLineEnd(size_t leafIndex, size_t leafStartOffset, size_t innerLineIndex, BufferCursor &result);
    void _updateNodes(size_t fromNodeIndex, size_t toNodeIndex);
    void _updateSingleNode(size_t nodeIndex);
};
}

#endif
