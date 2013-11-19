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

struct patricia *patricia_add(struct patricia *root, struct patricia *node) {
    struct patricia **branch = &root;
    size_t child_offset, parent_offset = 0;

    do {
        child_offset = patricia_prefix_compare(*branch, node, parent_offset);
        parent_offset = (*branch)->offset;

        if (child_offset < parent_offset) {
            break;
        }

        branch = (*branch)->next + patricia_prefix_bit(node, parent_offset);
    } while ((*branch)->offset > parent_offset);

    if (child_offset >= parent_offset) {
        child_offset = patricia_prefix_compare(*branch, node, parent_offset);
    }

    size_t bit = patricia_prefix_bit(*branch, child_offset);
    assert(bit == 0 || bit == 1);
    node->offset = child_offset;
    node->next[bit-0] = *branch;
    node->next[1-bit] = node;

    *branch = node;
    return root;
}

struct patricia *patricia_get(struct patricia *node, struct patricia *prefix) {
    size_t bit, offset;

    do {
        offset = node->offset;
        bit = patricia_prefix_bit(prefix, offset);
        node = node->next[bit];
    } while (offset < node->offset);

    return node->length == prefix->length && memcmp(node->prefix, prefix->prefix, prefix->length) == 0 ? node : NULL;
}

size_t patricia_prefix_compare(struct patricia *p1, struct patricia *p2, size_t offset) {
    size_t hi = offset / 2 / CHAR_BIT;
    size_t max = p1->length < p2->length ? p1->length : p2->length;

    if (hi >= max) {
        return (hi * CHAR_BIT + ~0U % CHAR_BIT) * 2;
    }

    while (p1->prefix[hi] == p2->prefix[hi]) {
        hi++;
        if (hi == max) {
            return (hi * CHAR_BIT + ~0U % CHAR_BIT) * 2;
        }
    }

    size_t lo = hi > offset / 2 / CHAR_BIT
              ? ~0U % CHAR_BIT
              : ~(offset / 2 + 1) % CHAR_BIT,
           sum = (unsigned char) p1->prefix[hi]
               ^ (unsigned char) p2->prefix[hi];

    while (lo > 0 && sum >> lo == 0) {
        lo--;
    }

    return (hi * CHAR_BIT + ~lo % CHAR_BIT) * 2 + 1;
}

size_t patricia_prefix_bit(struct patricia *node, size_t offset) {
    size_t hi = offset / 2 / CHAR_BIT;

    if (offset % 2 == 0 || hi >= node->length) {
        return hi < node->length;
    }

    return (node->prefix[hi] >> (~offset / 2 % CHAR_BIT)) & 1;
}

int patricia_inspect(struct patricia *node, size_t level) {
    printf("%*s%s.offset: %zu\n", 4*level, "", node->prefix, node->offset);
    printf("%*s%s.length: %zu\n", 4*level, "", node->prefix, node->length);

    printf("%*s%s.node[0]: %s (%zu)\n", 4*level, "", node->prefix, node->next[0]->prefix, node->next[0]->offset);
    if (node->next[0]->offset > node->offset) {
        patricia_inspect(node->next[0], level+1);
    }

    printf("%*s%s.node[1]: %s (%zu)\n", 4*level, "", node->prefix, node->next[1]->prefix, node->next[1]->offset);
    if (node->next[1]->offset > node->offset) {
        patricia_inspect(node->next[1], level+1);
    }

    return level;
}
