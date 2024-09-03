
    while (cin >> minterm)
    {
        int pos = 0;
        Landfill copy(L);
        do
        {
            copy.fill(minterm & 1 ? pos : -1);
            minterm >>= 1;
            pos++;
        } while (minterm > 0);
        copy.visualize(L);
        cout << "Roughness: " << copy.roughness() << endl;
    }