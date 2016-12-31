import sys
import re
import array
import binascii
import codecs
import pickle
import queue

class Node():
    def __init__(self, letter, freq):
        self.letter = letter
        self.freq = freq
        self.left = None
        self.right = None
        self.delete = False

    def height(self, node):
        if node is None:
            return 0
        else:
            left_height = self.height(node.left)
            right_height = self.height(node.right)

            if left_height > right_height:
                return left_height + 1
            else:
                return right_height + 1

    def traverse_level_order(self, root):
        h = self.height(root)
        for i in range(1, h+1):
            self.print_level(root, i)

    def print_level(self, root, level):
        if root is None:
            return
        if level == 1:
            print("{} - {}".format(root.letter, root.freq))
        elif level > 1:
            self.print_level(root.left, level - 1)
            self.print_level(root.right, level - 1)

class HuffmanTree():
    def __init__(self, _input):
        self._input = _input
        self.letter_dict = {}
        self._parse_input()
        self.node_list = self._fill_node_list()
        self._create_tree()
        self.root = self.node_list[0]
        self.encoding = {}
        self._encode_tree()
        self._write_to_disk()

    def _write_to_disk(self):
        buf = ""
        length = 0
        chunk = 0
        arr = array.array('B')
        with open(self._input, 'r') as f:
            for line in f:
                for word in re.findall(r'\S+|\n',line):
                    for letter in word:
                        buf += str(self.encoding[letter])

        for bit in buf:
            if bit == '1':
                chunk = (chunk << 1) | 0x01
            else:
                chunk = (chunk << 1)
            length += 1

            if length == 8:
                arr.append(chunk)
                chunk, length = 0, 0

        if length != 0:
            arr.append(chunk << (8-length))

        with open('a.bin', 'ab') as f:
            for byte in arr:
                length = len(str(byte))
                f.write(byte.to_bytes((length + 7) // 8, byteorder='big'))

    def _parse_input(self):
        try:
            with open(self._input, 'r') as f:
                self.letter_dict = self._create_letter_dict(f)
        except IOError:
            print("Unable to read file!")
            exit(1)

    def _create_letter_dict(self, contents):
        letter_dict = {}
        for line in contents:
            for word in re.findall(r'\S+|\n',line):
                for letter in word:
                    if letter not in letter_dict:
                        letter_dict[letter] = 1
                    else:
                        letter_dict[letter] += 1
        return letter_dict

    def _fill_node_list(self):
        node_list = []
        for letter in self.letter_dict:
            node = Node(letter, self.letter_dict[letter])
            node_list.append(node)
        return node_list

    def _create_tree(self):
        num_entries = len(self.node_list)
        while num_entries != 1:
            n_1 = None
            n_2 = None

            first = second = 100000000
            for i in range(0, len(self.node_list)):
                if self.node_list[i].freq < first:
                    second = first
                    n_2 = n_1
                    first = self.node_list[i].freq
                    n_1 = self.node_list[i]
                elif self.node_list[i].freq < second:
                    second = self.node_list[i].freq
                    n_2 = self.node_list[i]

            root_node = Node('', n_1.freq + n_2.freq)
            root_node.left = n_1
            root_node.right = n_2
            self.node_list.append(root_node)

            n_1.delete = n_2.delete = True

            for i in list(self.node_list):
                if i.delete:
                    self.node_list.remove(i)

            num_entries -= 1

    def _encode_tree(self):
        path = ['' for i in range(100)]
        encode_dict = {}
        self._encode(self.root, encode_dict, '', path, 0)

    def _encode(self, node, encode_dict, direction, path, pathlen):
        if node == None:
            return
        path[pathlen] = direction
        pathlen += 1

        if node.left is None and node.right is None:
            self.encoding[node.letter] = ''.join(path[1:pathlen])
        else:
            self._encode(node.left, encode_dict, '0', path, pathlen)
            self._encode(node.right, encode_dict, '1', path, pathlen)

class Decoder():
    def __init__(self, encoding):
        self.encoding = {v:k for k,v in encoding.items()}
        with open('tst3.pickle', 'wb') as h:
            pickle.dump(self.encoding, h, protocol=pickle.HIGHEST_PROTOCOL)

    def _read(self):
        with open('a.bin', 'rb') as f:
            byte = f.read()

        s = ""

        for bit in byte:
            value = format(int(bit), '#010b')
            s += str(value).replace('0b','')

        start, end, stuck = 0, 0, 0
        output = ''
        while True:
            if len(s) == 0 or stuck > 500:
                print(s)
                break
            try:
                output += self.encoding[s[start:end]]
                s = s[end:]
                start, end, stuck = 0,0,0
            except:
                end += 1
                stuck += 1

        print(output)

    def _check_encoding(self):
        for i in self.encoding:
            print(i, ' ', self.encoding[i])


if __name__ == '__main__':
    #sentence = "this is a sentence, this is not a paragraph. this is a sentence! so don't get it twisted ya hear? because other was this sentence would not be a sentence but a sentence would become a paragrah, which is pretty weird if you ask me if if if if if if if if"

    #t = HuffmanTree("file2.txt", True)
    #print()
    #t._preorder_traverse(t.root)
    #t._encode_tree()
    t = HuffmanTree("od.txt")
    #t._encode_tree()

    e = Decoder(t.encoding)
    e._check_encoding()
    e._read()
