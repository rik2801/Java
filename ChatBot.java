package Java;

import java.util.Scanner;

public class ChatBot {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            System.out.println("Welcome to Simple Chat App!");

            // Ask quiz questions
            int beginnerPoints = askBeginnerQuizQuestions(scanner);
            int intermediatePoints = askIntermediateQuizQuestions(scanner);
            int advancedPoints = askAdvancedQuizQuestions(scanner);

            // Determine the user's expertise level based on quiz results
            String expertiseLevel = determineExpertiseLevel(beginnerPoints, intermediatePoints, advancedPoints);
            System.out.println("\nYour Java expertise level: " + expertiseLevel + "\n");

            // Simulate chatting based on the determined expertise level
            while (true) {
                // User sends a message
                System.out.print("You: ");
                String userMessage = scanner.nextLine();
                System.out.println("\nSending: " + userMessage);

                // Simulate receiving a message from a friend based on expertise level
                String friendMessage = receiveMessage("BOT", userMessage, expertiseLevel);
                System.out.println("\nBOT: " + friendMessage);

                // Check if the user wants to stop the chat
                if (userMessage.equalsIgnoreCase("stop")) {
                    System.out.println("\nOkay, I stop here.");
                    break; // Exit the chat loop
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // Close the scanner in the finally block
            if (scanner != null) {
                scanner.close();
            }
        }
    }

    // Simulate receiving a message based on expertise level
    private static String receiveMessage(String sender, String message, String expertiseLevel) {
        // Customize responses based on expertise level
        switch (expertiseLevel) {
            case "beginner":
                return "Friend: " + formatResponse("It's great that you're starting to learn Java! For beginners, focus on the basics like variables, loops, and conditionals.");
            case "intermediate":
                return "Friend: " + formatResponse("For intermediate Java learners, consider diving deeper into topics like object-oriented programming, collections, and exception handling.");
            case "advanced":
                return "Friend: " + formatResponse("If you're an advanced Java developer, explore advanced topics like multithreading, design patterns, and Java frameworks.");
            default:
                return "Friend: " + formatResponse("Hello from " + sender + "! I'm here for a chat. If you have any questions or need advice, feel free to ask.");
        }
    }

    // Determine the user's expertise level based on quiz results
    private static String determineExpertiseLevel(int beginnerPoints, int intermediatePoints, int advancedPoints) {
        if (advancedPoints >= intermediatePoints && advancedPoints >= beginnerPoints) {
            return "advanced";
        } else if (intermediatePoints >= beginnerPoints) {
            return "intermediate";
        } else {
            return "beginner";
        }
    }

    // Ask beginner-level quiz questions
    private static int askBeginnerQuizQuestions(Scanner scanner) {
        System.out.println("Let's determine your Java expertise level. Answer the following questions:");

        int points = 0;


        points += askQuestion("What is Java used for?", "a) Web development", "b) Mobile app development", "c) Both a and b", "c", scanner);


        points += askQuestion("What is a variable?", "a) A constant value", "b) A placeholder for data", "c) A programming language", "b", scanner);

        return points;
    }

    // Ask intermediate-level quiz questions
    private static int askIntermediateQuizQuestions(Scanner scanner) {
        int points = 0;

        // Simulate user answering the question
        points += askQuestion("Question 3: What is an interface in Java?", "a) A graphical user interface", "b) A way to define a contract for classes", "c) A type of class", "b", scanner);

        // Add more questions and adjust points accordingly
        points += askQuestion("Question 4: What is the purpose of a try-catch block?", "a) To declare variables", "b) To handle exceptions", "c) To define loops", "b", scanner);

        return points;
    }

    // Ask advanced-level quiz questions
    private static int askAdvancedQuizQuestions(Scanner scanner) {
        int points = 0;

        // Simulate user answering the question
        points += askQuestion("Question 5: What is a lambda expression in Java?", "a) A mathematical expression", "b) An anonymous function", "c) A data type", "b", scanner);

        // Add more questions and adjust points accordingly
        points += askQuestion("Question 6: What is the purpose of the 'synchronized' keyword?", "a) To declare a variable", "b) To provide thread safety", "c) To define a class", "b", scanner);

        return points;
    }

    // Helper method to ask a multiple-choice question and return points
    private static int askQuestion(String question, String optionA, String optionB, String optionC, String correctAnswer, Scanner scanner) {
        System.out.println(question);
        System.out.println(optionA);
        System.out.println(optionB);
        System.out.println(optionC);

        int points = 0;

        // Simulate user answering the question
        String answer = scanner.nextLine().toLowerCase();
        if (answer.equals(correctAnswer)) {
            points++;
            System.out.println("Correct!\n");
        } else {
            System.out.println("Incorrect. The correct answer is: " + correctAnswer + "\n");
        }

        return points;
    }

    // Helper method to format response for better readability
    private static String formatResponse(String response) {
        return "\n" + response + "\n";
    }
}
