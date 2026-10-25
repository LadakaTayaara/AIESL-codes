from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity

corpus = [
    "Chronic kidney disease involves gradual loss of kidney function.",
    "Kidneys filter wastes and excess fluids from the blood.",
    "Symptoms include nausea, vomiting, fatigue, and weakness."
]

def reply(q):
    cm = CountVectorizer().fit_transform(corpus + [q])
    sim = cosine_similarity(cm[-1], cm[:-1]).flatten()
    best = sim.argmax()
    return corpus[best] if sim[best] > 0 else "I don't understand."

while True:
    try:
        q = input("You: ")
    except:
        break
    if q.lower() in ["bye", "exit"]: break
    print("Doc Bot:", reply(q))
