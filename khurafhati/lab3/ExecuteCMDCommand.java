package khurafhati.lab3; // Package names cannot contain backslashes or spaces

public class ExecuteCMDCommand {
    public static void main(String[] args) {
        try {
            // For Windows cmd built-ins like 'dir':
            ProcessBuilder builder = new ProcessBuilder("cmd.exe", "/c", "dir");

            // Redirects child process stdout and stderr directly to the Java console
            builder.inheritIO();

            Process process = builder.start();
            int exitCode = process.waitFor();

            System.out.println("\nProcess exited with code: " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}