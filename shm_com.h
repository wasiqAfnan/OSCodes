struct sm {
    int wr;            // 0 = consumer can read, 1 = producer is writing
    char st[2048];     // shared message
};
