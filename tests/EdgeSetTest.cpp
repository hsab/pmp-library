//=============================================================================
// Copyright (C) 2017 Daniel Sieger
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// =============================================================================

#include "gtest/gtest.h"

#include <pmp/EdgeSet.h>
#include <vector>

using namespace pmp;

class EdgeSetTest : public ::testing::Test
{
public:
    EdgeSet es;
};

TEST_F(EdgeSetTest, operatorNew)
{
    EdgeSet* es = new EdgeSet();
    EXPECT_EQ(es->nVertices(), size_t(0));
    EXPECT_EQ(es->nEdges(), size_t(0));
}

TEST_F(EdgeSetTest, operatorEq)
{
    EdgeSet es2 = es;
    EXPECT_EQ(es2.nVertices(), size_t(0));
}

TEST_F(EdgeSetTest, assignment)
{
    EdgeSet es2;
    es2.assign(es);
    EXPECT_EQ(es2.nVertices(), size_t(0));
}

TEST_F(EdgeSetTest, addRemove)
{
    Point p0(0,0,0);
    Point p1(1,0,0);
    Point p2(2,0,0);
    auto v0  = es.addVertex(p0);
    auto v1  = es.addVertex(p1);
    auto v2  = es.addVertex(p2);
    EXPECT_EQ(es.nVertices(), size_t(3));

    auto e0 = es.insertEdge(v0,v1);
    es.insertEdge(v1,v2);
    EXPECT_EQ(es.nEdges(), size_t(2));

    size_t nv(0);
    for (auto v : es.vertices())
    {
        if (v.isValid())
            nv++;
    }
    EXPECT_EQ(nv, size_t(3));

    size_t ne(0);
    for (auto e : es.edges())
    {
        if (e.isValid())
            ne++;
    }
    EXPECT_EQ(ne, size_t(2));

    size_t nh(0);
    for (auto h : es.halfedges())
    {
        if (h.isValid())
            nh++;
    }
    EXPECT_EQ(nh, size_t(4));

    size_t nvv = 0;
    for (auto vv : es.vertices(v1))
    {
        if (vv.isValid())
            nvv++;
    }
    EXPECT_EQ(nvv, size_t(2));

    size_t nvh = 0;
    for (auto vh : es.halfedges(v1))
    {
        if (vh.isValid())
            nvh++;
    }
    EXPECT_EQ(nvh, size_t(2));

    es.deleteEdge(es.edge(e0));
    EXPECT_TRUE(es.isDeleted(e0));
    es.garbageCollection();
    EXPECT_EQ(es.nEdges(), size_t(1));

    es.clear();
    EXPECT_EQ(es.nVertices(), size_t(0));
}

TEST_F(EdgeSetTest, read)
{
    es.read("data/3rings.knt");
    EXPECT_EQ(es.nVertices(), size_t(36));
    EXPECT_EQ(es.nEdges(), size_t(36));
}


//=============================================================================