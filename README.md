基于结构化知识的检索增强代码生成框架

面向大语言模型在算法编程任务中正确率不足的问题，围绕检索增强生成（RAG）思路，构建基于结构化知识的检索增强生成框架。通过引入外部算法知识，结合任务分解、知识检索、重排筛选与注入等机制，提升大模型代码生成能力。

## 仓库结构

当前仓库的主要目录如下：

```text
Knowledge-Augmented-Codegen/
├─ knowledge_base/         
├─ ProblemInfoCrawler/   
├─ evaluation/           
├─ src/
│  ├─ kb/                  
│  └─ rag/                 
└─ .gitignore
