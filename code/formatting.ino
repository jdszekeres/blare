String getFormattedTime(unsigned long epochTime) {
    int hours = (epochTime % 86400L) / 3600; // Calculate hours
    int minutes = (epochTime % 3600) / 60;   // Calculate minutes
    int seconds = epochTime % 60;            // Calculate seconds

    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, seconds);
    return String(buffer);
}

String getFormattedDate(unsigned long epochTime) {
    int days = epochTime / 86400L; // Calculate total days since epoch
    int year;
    for (int year = 1970; ; year++) {
        int daysInYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 366 : 365;
        if (days < daysInYear) {
            break;
        }
        days -= daysInYear;
    }
    for (int month = 1; month <= 12; month++) {
        int daysInMonth;
        if (month == 2) {
            daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        } else {
            daysInMonth = 31;
        }
        if (days < daysInMonth) {
            int date = days + 1; // Add 1 because days are zero-indexed
            char buffer[11];
            snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d", month, date, year);
            return String(buffer);
        }
        days -= daysInMonth;
    }
    return "Invalid date";
}

String getDayOfWeek(unsigned long epochTime) {
    int days = epochTime / 86400L; // Calculate total days since epoch
    int dayOfWeek = (days + 4) % 7; // January 1, 1970 was a Thursday (4)
    switch (dayOfWeek) {
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        default: return "";
    }
}