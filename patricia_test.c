/* Copyright (c) 2013, Sebastian Ramadan
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of the {organization} nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "patricia.h"

#define TEST1
#define TEST2
#define TEST3
#define TEST4

#define default_ptrie(node, ...) memcpy(node, &(struct patricia){ .prefix = "", .next = { node, node }, __VA_ARGS__ }, sizeof (struct patricia))
#define default_prefixed_ptrie(node, prefix_str, ...) default_ptrie(node, .prefix = prefix_str, .offset = strlen(prefix_str) * 2 * CHAR_BIT, .length = strlen(prefix_str))

int main(void) {
    struct patricia foo[32];
    struct patricia *bar = foo;
    struct patricia *root;

#ifdef TEST1
    puts("TEST1 running...");

    struct patricia *s = default_prefixed_ptrie(bar, "s"); bar++;
    struct patricia *e = default_prefixed_ptrie(bar, "e"); bar++;
    struct patricia *a = default_prefixed_ptrie(bar, "a"); bar++;
    struct patricia *r = default_prefixed_ptrie(bar, "r"); bar++;
    struct patricia *c = default_prefixed_ptrie(bar, "c"); bar++;
    struct patricia *h = default_prefixed_ptrie(bar, "h"); bar++;
    struct patricia *i = default_prefixed_ptrie(bar, "i"); bar++;
    struct patricia *n = default_prefixed_ptrie(bar, "n"); bar++;

    root = a;
    assert(patricia_get(root, a) == a || patricia_inspect(root, 0));
    root = patricia_add(root, s);
    assert(patricia_get(root, a) == a || patricia_inspect(root, 0));
    assert(patricia_get(root, s) == s || patricia_inspect(root, 0));
    root = patricia_add(root, e);
    assert(patricia_get(root, a) == a || patricia_inspect(root, 0));
    assert(patricia_get(root, s) == s || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    root = patricia_add(root, r);
    assert(patricia_get(root, a) == a || patricia_inspect(root, 0));
    assert(patricia_get(root, s) == s || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    assert(patricia_get(root, r) == r || patricia_inspect(root, 0));
    root = patricia_add(root, c);
    assert(patricia_get(root, a) == a || patricia_inspect(root, 0));
    assert(patricia_get(root, s) == s || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    assert(patricia_get(root, r) == r || patricia_inspect(root, 0));
    assert(patricia_get(root, c) == c || patricia_inspect(root, 0));
    root = patricia_add(root, h);
    assert(patricia_get(root, a) == a || patricia_inspect(root, 0));
    assert(patricia_get(root, s) == s || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    assert(patricia_get(root, r) == r || patricia_inspect(root, 0));
    assert(patricia_get(root, c) == c || patricia_inspect(root, 0));
    assert(patricia_get(root, h) == h || patricia_inspect(root, 0));
    root = patricia_add(root, i);
    assert(patricia_get(root, a) == a || patricia_inspect(root, 0));
    assert(patricia_get(root, s) == s || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    assert(patricia_get(root, r) == r || patricia_inspect(root, 0));
    assert(patricia_get(root, c) == c || patricia_inspect(root, 0));
    assert(patricia_get(root, h) == h || patricia_inspect(root, 0));
    assert(patricia_get(root, i) == i || patricia_inspect(root, 0));
    root = patricia_add(root, n);
    assert(patricia_get(root, a) == a || patricia_inspect(root, 0));
    assert(patricia_get(root, s) == s || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    assert(patricia_get(root, r) == r || patricia_inspect(root, 0));
    assert(patricia_get(root, c) == c || patricia_inspect(root, 0));
    assert(patricia_get(root, h) == h || patricia_inspect(root, 0));
    assert(patricia_get(root, i) == i || patricia_inspect(root, 0));
    assert(patricia_get(root, n) == n || patricia_inspect(root, 0));

    root = patricia_remove(root, c);
    assert(patricia_get(root, a) == a || patricia_inspect(root, 0));
    assert(patricia_get(root, s) == s || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    assert(patricia_get(root, r) == r || patricia_inspect(root, 0));
    assert(!patricia_contains(root, c) || patricia_inspect(root, 0));
    assert(patricia_get(root, h) == h || patricia_inspect(root, 0));
    assert(patricia_get(root, i) == i || patricia_inspect(root, 0));
    assert(patricia_get(root, n) == n || patricia_inspect(root, 0));

    root = patricia_remove(root, a);
    assert(!patricia_contains(root, a) || patricia_inspect(root, 0));
    assert(patricia_get(root, s) == s || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    assert(patricia_get(root, r) == r || patricia_inspect(root, 0));
    assert(!patricia_contains(root, c) || patricia_inspect(root, 0));
    assert(patricia_get(root, h) == h || patricia_inspect(root, 0));
    assert(patricia_get(root, i) == i || patricia_inspect(root, 0));
    assert(patricia_get(root, n) == n || patricia_inspect(root, 0));

    root = patricia_remove(root, s);
    assert(!patricia_contains(root, a) || patricia_inspect(root, 0));
    assert(!patricia_contains(root, s) || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    assert(patricia_get(root, r) == r || patricia_inspect(root, 0));
    assert(!patricia_contains(root, c) || patricia_inspect(root, 0));
    assert(patricia_get(root, h) == h || patricia_inspect(root, 0));
    assert(patricia_get(root, i) == i || patricia_inspect(root, 0));
    assert(patricia_get(root, n) == n || patricia_inspect(root, 0));

    root = patricia_remove(root, h);
    assert(!patricia_contains(root, a) || patricia_inspect(root, 0));
    assert(!patricia_contains(root, s) || patricia_inspect(root, 0));
    assert(patricia_get(root, e) == e || patricia_inspect(root, 0));
    assert(patricia_get(root, r) == r || patricia_inspect(root, 0));
    assert(!patricia_contains(root, c) || patricia_inspect(root, 0));
    assert(!patricia_contains(root, h) || patricia_inspect(root, 0));
    assert(patricia_get(root, i) == i || patricia_inspect(root, 0));
    assert(patricia_get(root, n) == n || patricia_inspect(root, 0));
#endif
#ifdef TEST2
    puts("TEST2 running...");

    struct patricia *smile =   default_prefixed_ptrie(bar, "smile"); bar++;
    struct patricia *smiled =  default_prefixed_ptrie(bar, "smiled"); bar++;
    struct patricia *smiles =  default_prefixed_ptrie(bar, "smiles"); bar++;
    struct patricia *smiling = default_prefixed_ptrie(bar, "smiling"); bar++;

    root = smile;
    assert(patricia_get(root, smile) == smile || patricia_inspect(root, 0));
    root = patricia_add(root, smiled);
    assert(patricia_get(root, smile) == smile || patricia_inspect(root, 0));
    assert(patricia_get(root, smiled) == smiled || patricia_inspect(root, 0));
    root = patricia_add(root, smiles);
    assert(patricia_get(root, smile) == smile || patricia_inspect(root, 0));
    assert(patricia_get(root, smiled) == smiled || patricia_inspect(root, 0));
    assert(patricia_get(root, smiles) == smiles || patricia_inspect(root, 0));
    root = patricia_add(root, smiling);
    assert(patricia_get(root, smile) == smile || patricia_inspect(root, 0));
    assert(patricia_get(root, smiled) == smiled || patricia_inspect(root, 0));
    assert(patricia_get(root, smiles) == smiles || patricia_inspect(root, 0));
    assert(patricia_get(root, smiling) == smiling || patricia_inspect(root, 0));

    root = patricia_remove(root, smile);
    assert(patricia_get(root, smiled) == smiled || patricia_inspect(root, 0));
    assert(patricia_get(root, smiles) == smiles || patricia_inspect(root, 0));
    assert(patricia_get(root, smiling) == smiling || patricia_inspect(root, 0));
#endif
#ifdef TEST3
    puts("TEST3 running...");

    struct patricia *now_node =    default_prefixed_ptrie(bar, "now"); bar++;
    struct patricia *is_node =     default_prefixed_ptrie(bar, "is"); bar++;
    struct patricia *the_node =    default_prefixed_ptrie(bar, "the"); bar++;
    struct patricia *time_node =   default_prefixed_ptrie(bar, "time"); bar++;
    struct patricia *for_node =    default_prefixed_ptrie(bar, "for"); bar++;
    struct patricia *theory_node = default_prefixed_ptrie(bar, "theory"); bar++;

    root = now_node;
    assert(patricia_get(root, now_node) == now_node || patricia_inspect(root, 0));
    root = patricia_add(root, is_node);
    assert(patricia_get(root, now_node) == now_node || patricia_inspect(root, 0));
    assert(patricia_get(root, is_node) == is_node || patricia_inspect(root, 0));
    root = patricia_add(root, the_node);
    assert(patricia_get(root, now_node) == now_node || patricia_inspect(root, 0));
    assert(patricia_get(root, is_node) == is_node || patricia_inspect(root, 0));
    assert(patricia_get(root, the_node) == the_node || patricia_inspect(root, 0));
    root = patricia_add(root, time_node);
    assert(patricia_get(root, now_node) == now_node || patricia_inspect(root, 0));
    assert(patricia_get(root, is_node) == is_node || patricia_inspect(root, 0));
    assert(patricia_get(root, the_node) == the_node || patricia_inspect(root, 0));
    assert(patricia_get(root, time_node) == time_node || patricia_inspect(root, 0));
    root = patricia_add(root, for_node);
    assert(patricia_get(root, now_node) == now_node || patricia_inspect(root, 0));
    assert(patricia_get(root, is_node) == is_node || patricia_inspect(root, 0));
    assert(patricia_get(root, the_node) == the_node || patricia_inspect(root, 0));
    assert(patricia_get(root, time_node) == time_node || patricia_inspect(root, 0));
    assert(patricia_get(root, for_node) == for_node || patricia_inspect(root, 0));
    root = patricia_add(root, theory_node);
    assert(patricia_get(root, now_node) == now_node || patricia_inspect(root, 0));
    assert(patricia_get(root, is_node) == is_node || patricia_inspect(root, 0));
    assert(patricia_get(root, the_node) == the_node || patricia_inspect(root, 0));
    assert(patricia_get(root, time_node) == time_node || patricia_inspect(root, 0));
    assert(patricia_get(root, for_node) == for_node || patricia_inspect(root, 0));
    assert(patricia_get(root, theory_node) == theory_node || patricia_inspect(root, 0));
#endif
#ifdef TEST4
    puts("TEST4 running...");

    struct patricia *some_node =           default_prefixed_ptrie(bar, "SOME"); bar++;
    struct patricia *abacus_node =         default_prefixed_ptrie(bar, "ABACUS"); bar++;
    struct patricia *something_node =      default_prefixed_ptrie(bar, "SOMETHING"); bar++;
    struct patricia *b_node =              default_prefixed_ptrie(bar, "B"); bar++;
    struct patricia *abracadabra_node =    default_prefixed_ptrie(bar, "ABRACADABRA"); bar++;
    struct patricia *this_node =           default_prefixed_ptrie(bar, "THIS"); bar++;
    struct patricia *somerset_node =       default_prefixed_ptrie(bar, "SOMERSET"); bar++;

    root = some_node;
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOME", .length = 4 }) == some_node || patricia_inspect(root, 0));
    root = patricia_add(root, abacus_node);
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOME", .length = 4 }) == some_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "ABACUS", .length = 6 }) == abacus_node || patricia_inspect(root, 0));
    root = patricia_add(root, something_node);
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOME", .length = 4 }) == some_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "ABACUS", .length = 6 }) == abacus_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOMETHING", .length = 9 }) == something_node || patricia_inspect(root, 0));
    root = patricia_add(root, b_node);
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOME", .length = 4 }) == some_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "ABACUS", .length = 6 }) == abacus_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOMETHING", .length = 9 }) == something_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "B", .length = 1 }) == b_node || patricia_inspect(root, 0));
    root = patricia_add(root, abracadabra_node);
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOME", .length = 4 }) == some_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "ABACUS", .length = 6 }) == abacus_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOMETHING", .length = 9 }) == something_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "B", .length = 1 }) == b_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "ABRACADABRA", .length = 11 }) == abracadabra_node || patricia_inspect(root, 0));
    root = patricia_add(root, this_node);
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOME", .length = 4 }) == some_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "ABACUS", .length = 6 }) == abacus_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOMETHING", .length = 9 }) == something_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "B", .length = 1 }) == b_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "ABRACADABRA", .length = 11 }) == abracadabra_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "THIS", .length = 4 }) == this_node || patricia_inspect(root, 0));
    root = patricia_add(root, somerset_node);
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOME", .length = 4 }) == some_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "ABACUS", .length = 6 }) == abacus_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOMETHING", .length = 9 }) == something_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "B", .length = 1 }) == b_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "ABRACADABRA", .length = 11 }) == abracadabra_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "THIS", .length = 4 }) == this_node || patricia_inspect(root, 0));
    assert(patricia_get(root, &(struct patricia){ .prefix = "SOMERSET", .length = 8 }) == somerset_node || patricia_inspect(root, 0));
#endif

    puts("PATRICIA tests completed successfully");
    puts("-------------------------------------");
    return 0;
}