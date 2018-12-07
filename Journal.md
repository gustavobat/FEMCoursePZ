# Journal

I'll use this file to write down my experiments and thoughts during the process so I can revisit it every once in a while and be proud of how much I learned.
An extra challenge I've set to myself is to use modern C++ as much as possible. I hope I can finally master std::functions by the end of this study.

As a side experiment, once this document is finished I'll try playing around with pandoc to convert this Markdown into LaTeX using my report template. Just 'cause I love LaTeX.

#### Day 0 - *"You look like a capable young man! I wonder if you seek the knowledge of the ~~Elder Scrolls~~ Finite Element Method."*

The task of developing a mini NeoPZ, a Finite Element Method library, has been suddenly assigned to me. ,

What I know so far is that I need to start by implement the Gauss-Legendre rule. 
I want everything to be as parametric as possible, so I need an algorithm to calculate the weights for whatever order of approximation one might use. 

After a quick (like 10 min quick) read on the internet, I realized that articles on the Gauss-Legendre rule tend to omit how weights are calculated with the excuse of it being "out of scope".
That's annoying, I need to research deeper. 
