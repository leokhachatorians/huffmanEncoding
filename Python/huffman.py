import sys
import re
import array
import binascii
import codecs

class Node():
    def __init__(self,  word, freq):
        self.word = word
        self.freq = freq
        self.left = None
        self.right = None
        self.delete = False

class HuffmanTree():
    def __init__(self, _input, is_a_file=False):
        self._input = _input
        self.is_a_file = is_a_file
        self.word_dict = {}
        self._parse_input()
        self.node_list = self._fill_node_list()
        self._create_tree()
        self.root = self.node_list[0]
        self.encoding = {}
        self._encode_tree()
        self._write_to_disk()

    def _write_to_disk(self):
        for i in self.encoding:
            print(i,self.encoding[i])

        buf = ""
        length = 0
        chunk = 0
        arr = array.array('B')
        with open(self._input, 'r') as f:
            for line in f:
                for word in line.split():
                    word += ' '
                    buf += str(self.encoding[word])

        for bit in buf:
            if bit == '1':
                chunk = (chunk << 1) | 0x01
            else:
                chunk = (chunk << 1)
            length += 1

            if length == 8:
                arr.extend([chunk])
                chunk, length = 0, 0

        if length != 0:
            arr.extend([chunk << (8-length)])

        with open('a.bin', 'ab') as f:
            for byte in arr:
                length = len(str(byte))
                f.write(byte.to_bytes((length + 7) // 8, byteorder='big'))
                #print(byte.to_bytes((length + 7) // 8, byteorder='big'))
                #print("Here", binascii.hexlify(byte.to_bytes((length + 7) // 8, byteorder='big')))

    def _parse_input(self):
        if self.is_a_file:
            try:
                with open(self._input, 'r') as f:
                    self.word_dict = self._create_word_dict(f, is_file=True)
            except IOError:
                print("Unable to read file!")
                exit(1)
        else:
            self.word_dict = self._create_word_dict(self._input)

    def _create_word_dict(self, contents, is_file=False):
        word_dict = {}
        if is_file:
            for line in contents:
                for word in line.split():
                    word += ' '
                    if word not in word_dict:
                        word_dict[word] = 1
                    else:
                        word_dict[word] += 1
        else:
            for word in contents.split():
                word += ' '
                if word not in word_dict:
                    word_dict[word] = 1
                else:
                    word_dict[word] += 1
        return word_dict

    def _fill_node_list(self):
        node_list = []
        for word in self.word_dict:
            node = Node(word, self.word_dict[word])
            node_list.append(node)
        return node_list

    def _create_tree(self):
        num_entries = len(self.node_list)
        while num_entries != 1:
            n_1 = None
            n_2 = None

            first = second = 100000
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
            self.node_list.insert(0,root_node)

            n_1.delete = n_2.delete = True

            for i in list(self.node_list):
                if i.delete:
                    self.node_list.remove(i)

            num_entries -= 1

    def _encode_tree(self):
        path = ['' for i in range(1000)]
        encode_dict = {}
        self._encode(self.root, encode_dict, '', path, 0)

    def _encode(self, node, encode_dict, direction, path, pathlen):
        if node == None:
            return
        path[pathlen] = direction
        pathlen += 1

        if (node.left == None and node.right == None):
            self.encoding[node.word] = ''.join(path)
        else:
            self._encode(node.left, encode_dict, '0', path, pathlen)
            self._encode(node.right, encode_dict, '1', path, pathlen)

class Decoder():
    def __init__(self, encoding):
        self.encoding = {v:k for k,v in encoding.items()}

    def _read(self):
        with open('a.bin', 'rb') as f:
            byte = f.read()

        s = ""

        for bit in byte:
            value = format(int(bit), '#010b')
            s += str(value).replace('0b','')

        start, end = 0,0
        output = ''
        while True:
            if len(s) == 0:
                break
            try:
                output += self.encoding[s[start:end]]
                s = s[end:]
                start, end = 0,0
            except:
                end += 1
                print(s[end:])

        print(output)



            #print(bin(format(int(bit), '#08b')))

            #rpint(' '.join(str(ord(c)) for c in str(byte)))
            #p#rint(byte)
            #print(codecs.decode(byte, "hex"))

    def _check_encoding(self):
        for i in self.encoding:
            print(i, ' ', self.encoding[i])





if __name__ == '__main__':
    #sentence = "this is a sentence, this is not a paragraph. this is a sentence! so don't get it twisted ya hear? because other was this sentence would not be a sentence but a sentence would become a paragrah, which is pretty weird if you ask me if if if if if if if if"

    t = HuffmanTree("file2.txt", True)
    #print()
    #t._preorder_traverse(t.root)
    #t._encode_tree()
    #t = HuffmanTree("od.txt", True)
    #print(t.word_dict)
    t._encode_tree()

    e = Decoder(t.encoding)
    e._read()
