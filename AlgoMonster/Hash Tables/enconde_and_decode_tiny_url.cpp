#include <unordered_map>
#include <string>

class Solution {
public:
    std::unordered_map<int, std::string> urlMap;
    const std::string baseURL = "http://tinyurl.com/";
    int id = 1;

    std::string encode(std::string longUrl) {
        // Map the current ID to the provided long URL
        urlMap[id] = longUrl;
        return baseURL + std::to_string(id++);
    }

    std::string decode(std::string shortUrl) {
        // Extract the ID from the short URL
        int id = std::stoi(shortUrl.substr(baseURL.size()));
        return urlMap[id];
    }
};