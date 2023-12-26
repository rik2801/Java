package Java;
import java.text.NumberFormat;
import java.time.LocalDate;
import java.util.Scanner;
import java.time.Instant;

public class MortgageCalculator{
    final static byte monthsInAYear = 12;
    final static byte percent = 100;
    // Get the current date
    static LocalDate currentDate = LocalDate.now();
    public static void main (String args[])
    {

        double principal= readNumber("Principal: $ ", 1000, 1000000);
        double annualInterestRate = readNumber("Annual Interest Rate (%):  ", 0.1, 30);
        double periodYears =readNumber("Years: ", 1, 30);
        printMortgage(principal, annualInterestRate, periodYears); //created using refactor >>> extract method to reduce LOC in main method
        printPaymentSchedule(periodYears, principal, annualInterestRate); //created using refactor >>> extract method to reduce LOC in main method
    }

    private static void printPaymentSchedule(double periodYears, double principal, double annualInterestRate) {
        System.out.println("\n PAYMENT SCHEDULE \n -------------------\n");
        for (short month = 1; month <= periodYears * monthsInAYear; month++){
            double balance = calculateBalance(principal, annualInterestRate, periodYears, month); // why month???? >>> this will eventually attribute to the fourth parameter in calculateBalance()
            // Add one month to the current date
            currentDate=currentDate.plusMonths(1);
            System.out.println("$ " + balance + "\tthe next installment is at \t" +currentDate);
        }
    }

    private static void printMortgage(double principal, double annualInterestRate, double periodYears) {
        System.out.println("\nMORTGAGE\n-------------");
        System.out.println("Your mortgage contract of : $ " + calculateMortgage(principal, annualInterestRate, periodYears)+"\ton "+currentDate); // today's date integration
    }

    public static double readNumber(String prompt, double min, double max){
        Scanner scanner = new Scanner(System.in);
        double value;
        while(true) {
            System.out.print(prompt);
            value = scanner.nextFloat();
            if(value >= min && value <= max)
                break;
            System.out.println("Enter a number between " + min + " and " + max);}
        return value;
    }

    //mortgage calculator
    public static double calculateMortgage(
            double principal,
            double annualInterestRate,
            double periodYears) //ask M why redundant?
    {
        double numberOfPayments = periodYears * monthsInAYear; // numberOfPayments
        double monthlyInterestRate = annualInterestRate / (monthsInAYear * percent); // monthlyInterestRate

        double mortgage = principal * (monthlyInterestRate * Math.pow(1+ monthlyInterestRate, numberOfPayments) / (Math.pow(1+ monthlyInterestRate , numberOfPayments) - 1));
        mortgage =  Math.round(mortgage * 100.00) / 100.00;
        return mortgage;
    }

    public static double calculateBalance(
            double principal,
            double annualInterestRate,
            double periodYears,
            short numberOfPaymentsMade){

        short numberOfPayments = (short) (periodYears * monthsInAYear); // numberOfPayments
        double monthlyInterestRate = annualInterestRate / (monthsInAYear * percent); // monthlyInterestRate

        double balance = principal
                * (Math.pow(1 +  monthlyInterestRate, numberOfPayments) - Math.pow(1+monthlyInterestRate, numberOfPaymentsMade))
                / (Math.pow(1 +  monthlyInterestRate, numberOfPayments) - 1);
        balance =  Math.round(balance * 100.00) / 100.00;
        return balance;
    }
}
