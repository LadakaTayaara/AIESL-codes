"""
Problem: Medical / Doctor Chatbot (Assignment 7)
Technique: Natural Language Processing (NLP) - Information Retrieval via Cosine Similarity

Concept:
- Bag of Words (BoW) model using CountVectorizer: Converts sentences into word frequency vectors.
- Cosine Similarity: Measures the cosine of the angle between two multi-dimensional vectors.
    Formula: Cosine_Similarity(A, B) = (A . B) / (||A|| * ||B||)
    Range: [0, 1] where 1 means identical word distribution and 0 means no shared words.
- When the user asks a question 'q', it is vectorized along with the medical knowledge corpus.
- The sentence in the corpus with the highest cosine similarity is returned as the bot's reply.
"""

from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity

# Medical knowledge base (Corpus of facts)
corpus = [
    "Chronic kidney disease involves gradual loss of kidney function.",
    "Kidneys filter wastes and excess fluids from the blood.",
    "Symptoms include nausea, vomiting, fatigue, and weakness."
]

def reply(q):
    """
    Finds and returns the most relevant fact from the corpus for user query 'q'.
    """
    # Combine knowledge base with user question and build the Bag-of-Words matrix
    # Shape of cm: (num_corpus_docs + 1, num_unique_words)
    cm = CountVectorizer().fit_transform(corpus + [q])

    # cm[-1] is the user's vectorized query
    # cm[:-1] are all the knowledge base documents
    # Compute cosine similarity between user query and each knowledge base sentence
    sim = cosine_similarity(cm[-1], cm[:-1]).flatten()

    # Find index of the most similar sentence
    best = sim.argmax()

    # Return the best matching sentence if similarity > 0, otherwise fallback
    return corpus[best] if sim[best] > 0 else "I don't understand."

# Interactive Chatbot conversation loop
print("Doc Bot: Hello! Ask me about kidney disease (type 'bye' or 'exit' to quit).")
while True:
    try:
        q = input("You: ")
    except (EOFError, KeyboardInterrupt):
        break

    # Exit condition
    if q.lower() in ["bye", "exit"]:
        print("Doc Bot: Goodbye! Take care.")
        break

    # Get response and display
    print("Doc Bot:", reply(q))
