import nltk

class Analyzer():
    """Implements sentiment analysis."""
    # load the words into lists 
    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        self.negatives = []
        with open("negative-words.txt") as negative:
            for line in negative:
                if line.startswith((";", " ")):
                    continue
                else:
                    self.negatives.extend(line.split())

        self.positives = []
        with open("positive-words.txt") as positive:
            for line in positive:
                if line.startswith((";", " ")):
                    continue
                else:
                    self.positives.extend(line.split())
            
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        
        #TODO assign each word in text a value -1, 0, 1, calculate texts total score
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        score = 0
        for token in tokens:
            token.lower()
            if token in self.positives:
                score+=1
            elif token in self.negatives:
                score=-1
                
        return score
