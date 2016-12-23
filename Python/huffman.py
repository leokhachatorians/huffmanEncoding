import sys

class TreeBuilder():
    def __init__(self, _input, is_a_file=False):
        self._input = _input
        self.is_a_file = is_a_file
        self.word_dict = {}

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
                    if word not in word_dict:
                        word_dict[word] = 1
                    else:
                        word_dict[word] += 1
        else:
            for word in contents.split():
                if word not in word_dict:
                    word_dict[word] = 1
                else:
                    word_dict[word] += 1
        return word_dict


class Node():
    def __init__(self,  word, freq):
        self.word = word
        self.freq = freq
        self.left = None
        self.right = None
        self.delete = False


if __name__ == '__main__':
    word_dict = {}
    node_list = []
    sentence = "this is a sentence, this is not a paragraph. this is a sentence! so don't get it twisted ya hear?"
    #sentence = "a a a a b b b c c d e"

    for word in sentence.split():
        if word not in word_dict:
            word_dict[word] = 1
        else:
            word_dict[word] += 1

    for word in word_dict:
        node = Node(word, word_dict[word])
        node_list.append(node)

    print("Nodes: ", len(node_list))

    for i in node_list:
        print(i.word, ' ', i.freq)
    print()


    num_words = len(node_list)

    while num_words != 1:
        n_1 = None
        n_2 = None

        first = second = 100000
        for i in range(0, len(node_list)):
            if node_list[i].freq < first:
                second = first
                n_2 = n_1
                first = node_list[i].freq
                n_1 = node_list[i]
            elif node_list[i].freq < second:
                second = node_list[i].freq
                n_2 = node_list[i]

        root_node = Node('', n_1.freq + n_2.freq)
        root_node.left = n_1
        root_node.right = n_2
        node_list.append(root_node)

        n_1.delete = n_2.delete = True

        for i in list(node_list):
            if i.delete:
                print(i.word)
                node_list.remove(i)

        #node_list[:] = [n for n in node_list if n.delete]

        print("Nodes: ", len(node_list))
        for i in node_list:
            print(i.word, ' ', i.freq)
        print()
        num_words -= 1

    t = TreeBuilder(sentence, False)
    t._parse_input()
    print(t.word_dict)
    t = TreeBuilder("file.txt", True)
    t._parse_input()
    print(t.word_dict)


