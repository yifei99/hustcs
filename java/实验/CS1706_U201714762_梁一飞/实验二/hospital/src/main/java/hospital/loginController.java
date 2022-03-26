package hospital;

import com.jfoenix.controls.*;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.KeyCode;
import javafx.stage.Stage;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.EventObject;

import static java.lang.System.exit;

public class loginController {
    @FXML
    JFXTextField inputUsername;
    @FXML
    JFXPasswordField inputPassword;
    @FXML
    JFXButton buttonLoginDoctor;
    @FXML
    JFXButton buttonLoginPatient;
    @FXML
    JFXButton buttonExit;
    @FXML
    Label labelStatus;

    @FXML
    void initialize() {
        buttonLoginDoctor.setOnKeyReleased(keyEvent -> {
            try {
                if (keyEvent.getCode() == KeyCode.ENTER)
                    doctorLogin();
            } catch (IOException e) {
            }
        });

        buttonLoginPatient.setOnKeyReleased(keyEvent -> {
            try {
                if (keyEvent.getCode() == KeyCode.ENTER)
                    patientLogin();
            } catch (IOException e) {
            }
        });

        buttonExit.setOnKeyReleased(keyEvent -> {
            if (keyEvent.getCode() == KeyCode.ENTER)
                exit(0);
        });
    }

    @FXML
    void doctorLogin() throws IOException {
        if (!validateUserNameAndPassword())
            return;

        ResultSet result = DBConnector.getInstance().getDoctorInfo(inputUsername.getText().trim());
        if (result == null) {
            labelStatus.setText("读取数据库错误，请联系管理员。");
            labelStatus.setStyle("-fx-text-fill: red;");
        }

        try {
            if (!result.next()) {
                labelStatus.setText("用户不存在");
                labelStatus.setStyle("-fx-text-fill: red;");
                return;
            } else if (!result.getString(Config.NameTableColumnDoctorPassword).equals(inputPassword.getText())) {
                labelStatus.setText("密码错误");
                labelStatus.setStyle("-fx-text-fill: red;");
                return;
            }

            doctorController.doctorName = result.getString(Config.NameTableColumnDoctorName);
            doctorController.doctorNumber = result.getString(Config.NameTableColumnDoctorNumber);

            DBConnector.getInstance().updateDoctorLoginTime(
                    result.getString(Config.NameTableColumnDoctorNumber),
                    LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")));

            Parent Operation_Parent1 = FXMLLoader.load(getClass().getResource("Doctor.fxml"));
            Scene Operation_Creating_Scene = new Scene(Operation_Parent1);
            Operation_Creating_Scene.getStylesheets().add(getClass().getResource("Main.css").toExternalForm());
            EventObject event = null;
            Stage CreateOperation_Stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            CreateOperation_Stage.hide();
            CreateOperation_Stage.setScene(Operation_Creating_Scene);
            CreateOperation_Stage.show();
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }
    }

    @FXML
    void patientLogin() throws IOException {
        if (!validateUserNameAndPassword())
            return;

        ResultSet result = DBConnector.getInstance().getPatientInfo(inputUsername.getText().trim());
        if (result == null) {
            labelStatus.setText("读取数据库错误，请联系管理员。");
            labelStatus.setStyle("-fx-text-fill: red;");
        }

        try {
            if (!result.next()) {
                labelStatus.setText("用户不存在");
                labelStatus.setStyle("-fx-text-fill: red;");
                return;
            } else if (!result.getString(Config.NameTableColumnPatientPassword).equals(inputPassword.getText())) {
                labelStatus.setText("密码错误");
                labelStatus.setStyle("-fx-text-fill: red;");
                return;
            }
            patientController.patientName = result.getString(Config.NameTableColumnPatientName);
            patientController.patientBalance = result.getDouble(Config.NameTableColumnPatientBalance);
            patientController.patientNumber = result.getString(Config.NameTableColumnPatientNumber);

            DBConnector.getInstance().updatePatientLoginTime(
                    result.getString(Config.NameTableColumnPatientNumber),
                    LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")));

            Parent Operation_Parent1 = FXMLLoader.load(getClass().getResource("Patient.fxml"));
            Scene Operation_Creating_Scene = new Scene(Operation_Parent1);
            Operation_Creating_Scene.getStylesheets().add(getClass().getResource("Main.css").toExternalForm());
            EventObject event = null;
            Stage CreateOperation_Stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            CreateOperation_Stage.hide();
            CreateOperation_Stage.setScene(Operation_Creating_Scene);
            CreateOperation_Stage.show();
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }
    }

    private boolean validateUserNameAndPassword() {
        if (inputUsername.getText().isEmpty()) {
            inputUsername.setStyle("-fx-background-color: pink;");
            labelStatus.setText("请输入用户名");
            labelStatus.setStyle("-fx-text-fill: red;");
            return false;
        }
        if (inputPassword.getText().isEmpty()) {
            inputPassword.setStyle("-fx-background-color: pink;");
            labelStatus.setText("请输入密码");
            labelStatus.setStyle("-fx-text-fill: red;");
            return false;
        }

        labelStatus.setText("登录中...");
        labelStatus.setStyle("");
        return true;
    }

    @FXML
    void onInputUsernameAction() {
        inputUsername.setStyle("");
    }

    @FXML
    void onInputPasswordAction() {
        inputPassword.setStyle("");
    }

    @FXML
    void buttonExitClicked() {
        exit(0);
    }
}
