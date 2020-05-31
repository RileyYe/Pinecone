# 不会真的有人看得懂缩写吧.py
import requests


def GetCorpus(FileName: str) -> dict:
    Map = dict()
    File = open(FileName, encoding="UTF-8")
    for Items in File.readlines():
        Map[Items.split()[0]] = Items.split()[1]
    return Map


def MaxMatchAndTransfer(Corpus: dict, Text: str) -> str:
    max_len = max([len(item) for item in Corpus.keys()])
    Transferred = []
    Start = 0
    while Start != len(Text):
        Index = Start + max_len
        if Index > len(Text):
            Index = len(Text)
        for i in range(max_len):
            if Corpus.get(Text[Start:Index]) is None and len(Text[Start:Index]) == 1:
                Transferred.append(Text[Start:Index])
                Start = Index
                break
            if Corpus.get(Text[Start:Index]) is not None:
                Transferred.append(Corpus[Text[Start:Index]])
                Start = Index
                break
            Index += -1
    return "".join(Transferred)


Text: str = "我他妈笑死，有一说一，真的有够阴阳怪气的呢.\n是漂亮姐姐啊，啊我死了。"

Url = r"https://gitee.com/RileyYe/Pinecone/raw/master/cppHomework/Corpus.txt"
r = requests.get(Url)
with open("Corpus.txt", "wb") as Corpus:
    Corpus.write(r.content)
print(MaxMatchAndTransfer(GetCorpus("Corpus.txt"), Text))
