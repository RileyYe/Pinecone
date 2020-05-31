# 不会真的有人看得懂缩写吧.py
import requests



def GetMap(FileName: str) -> dict:
    Map: dict = dict()
    File = open(FileName, encoding="UTF-8")
    for Items in File.readlines():
        Map[Items.split()[0]] = Items.split()[1]
    return Map


def MaxMatchAndTransfer(Corpus: dict, Text: str) -> str:
    max_len: int = max([len(item) for item in Corpus.keys()])
    Transferred: list = []
    Start: int = 0
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


def DownloadCorpus(Url: str, FileName: str) -> None:
    r = requests.get(Url)
    with open(FileName, "wb") as Corpus:
        Corpus.write(r.content)


Text: str = "我他妈笑死，有一说一，真的有够阴阳怪气的呢.\n是漂亮姐姐啊，啊我死了。"

Url: str = r"https://gitee.com/RileyYe/Pinecone/raw/master/cppHomework/Corpus.txt"

DownloadCorpus(Url, "Corpus.txt")
print(MaxMatchAndTransfer(GetMap("Corpus.txt"), Text))
