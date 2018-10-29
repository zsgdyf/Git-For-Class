import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.HashMap;
import java.util.Scanner;
import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;

public class CloudComputing {
    public static void sortByValue(Map<String, Integer> wordCount) {
        List<Map.Entry<String, Integer>> wordList = new ArrayList<>(wordCount.entrySet());
        Collections.sort(wordList, new Comparator<Map.Entry<String, Integer>>() {
            public int compare(Entry<String, Integer> x, Entry<String, Integer> y) {
                //return y.getValue().toString().compareTo(x.getValue().toString());
                return y.getValue() - x.getValue();
            }
        });
        for (Map.Entry<String, Integer> word : wordList.subList(0, 3)) {
            System.out.println("[" + word.getKey() + ", " + word.getValue() + "]");
        }
    }
    public static void wordCount(String words) {
        Map<String, Integer> wordCount = new HashMap<>();
        String[] word = words.split("\\W+");
        /*
        for (String a : word) {
            System.out.println("[" + a + "]");
        }
        */
        for (int i = 0; i < word.length; i++) {
            String key = word[i].toLowerCase();
            if (!wordCount.containsKey(key) && key != "") {
                wordCount.put(key, 1);
            } else {
                int value = wordCount.get(key);
                wordCount.put(key, ++value);
            }
        }
        /*
        wordCount.forEach((key, value) -> {
            System.out.println(key + "----" + value);
        });
        */
        /*
        for (Map.Entry<String, Integer> entry : wordCount.entrySet()) {
            System.out.println(entry.getKey() + "----" + entry.getValue());
        }
        */
        sortByValue(wordCount);
    }

    public static void main(String[] args) {
        System.out.print("Please input a sentence: \n");
        String words = "";
        //Scanner in = new Scanner(System.in);
        try {
            Scanner in = new Scanner(Paths.get("data.dat"), "UTF-8");
            while (in.hasNextLine()) {
                words = words + in.nextLine();
            }
            wordCount(words);
            in.close();
        } catch(IOException e) {}   
    }
}