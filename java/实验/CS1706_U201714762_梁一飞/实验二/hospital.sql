/*
Navicat MySQL Data Transfer

Source Server         : abc
Source Server Version : 80011
Source Host           : localhost:3306
Source Database       : hospital

Target Server Type    : MYSQL
Target Server Version : 80011
File Encoding         : 65001

Date: 2020-05-23 12:42:18
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for t_brxx
-- ----------------------------
DROP TABLE IF EXISTS `t_brxx`;
CREATE TABLE `t_brxx` (
  `BRBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `BRMC` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `DLKL` char(8) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `YCJE` decimal(10,2) NOT NULL,
  `DLRQ` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`BRBH`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_brxx
-- ----------------------------
INSERT INTO `t_brxx` VALUES ('001', '张三', '111', '779.38', '2020-05-23 12:21:30');
INSERT INTO `t_brxx` VALUES ('002', '李四', '111', '1000.00', '2020-05-23 01:14:16');
INSERT INTO `t_brxx` VALUES ('003', '王五', '111', '1000.00', '2020-05-23 01:14:18');
INSERT INTO `t_brxx` VALUES ('004', '马六', '111', '1000.00', '2020-05-23 01:14:20');
INSERT INTO `t_brxx` VALUES ('005', '赵七', '111', '1000.00', '2020-05-23 01:14:22');
INSERT INTO `t_brxx` VALUES ('006', '胡九', '111', '1000.00', '2020-05-23 01:14:25');

-- ----------------------------
-- Table structure for t_ghxx
-- ----------------------------
DROP TABLE IF EXISTS `t_ghxx`;
CREATE TABLE `t_ghxx` (
  `GHBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `HZBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `YSBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `BRBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `GHRC` int(11) NOT NULL,
  `THBZ` tinyint(1) NOT NULL,
  `GHFY` decimal(8,2) NOT NULL,
  `RQSJ` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`GHBH`),
  KEY `catid` (`HZBH`),
  KEY `docid` (`YSBH`),
  KEY `pid` (`BRBH`),
  CONSTRAINT `t_ghxx_ibfk_1` FOREIGN KEY (`HZBH`) REFERENCES `t_hzxx` (`HZBH`),
  CONSTRAINT `t_ghxx_ibfk_2` FOREIGN KEY (`YSBH`) REFERENCES `t_ksys` (`YSBH`),
  CONSTRAINT `t_ghxx_ibfk_3` FOREIGN KEY (`BRBH`) REFERENCES `t_brxx` (`BRBH`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_ghxx
-- ----------------------------
INSERT INTO `t_ghxx` VALUES ('000001', '002', '001', '001', '1', '0', '6.43', '2020-05-23 01:12:35');
INSERT INTO `t_ghxx` VALUES ('000002', '002', '001', '001', '2', '0', '6.43', '2020-05-23 01:12:39');
INSERT INTO `t_ghxx` VALUES ('000003', '006', '003', '001', '1', '0', '14.20', '2020-05-23 01:24:13');
INSERT INTO `t_ghxx` VALUES ('000004', '005', '004', '001', '1', '0', '58.53', '2020-05-23 12:17:22');
INSERT INTO `t_ghxx` VALUES ('000005', '002', '001', '001', '3', '0', '6.43', '2020-05-23 12:21:10');
INSERT INTO `t_ghxx` VALUES ('000006', '002', '001', '001', '4', '0', '6.43', '2020-05-23 12:21:11');
INSERT INTO `t_ghxx` VALUES ('000007', '002', '001', '001', '5', '0', '6.43', '2020-05-23 12:21:12');
INSERT INTO `t_ghxx` VALUES ('000008', '002', '001', '001', '6', '0', '6.43', '2020-05-23 12:21:14');
INSERT INTO `t_ghxx` VALUES ('000009', '002', '001', '001', '7', '0', '6.43', '2020-05-23 12:21:15');
INSERT INTO `t_ghxx` VALUES ('000010', '002', '001', '001', '8', '0', '6.43', '2020-05-23 12:21:15');
INSERT INTO `t_ghxx` VALUES ('000011', '002', '001', '001', '9', '0', '6.43', '2020-05-23 12:21:17');
INSERT INTO `t_ghxx` VALUES ('000012', '002', '001', '001', '10', '0', '6.43', '2020-05-23 12:21:18');
INSERT INTO `t_ghxx` VALUES ('000013', '002', '001', '001', '11', '0', '6.43', '2020-05-23 12:21:19');
INSERT INTO `t_ghxx` VALUES ('000014', '002', '001', '001', '12', '0', '6.43', '2020-05-23 12:21:20');
INSERT INTO `t_ghxx` VALUES ('000015', '002', '001', '001', '13', '0', '6.43', '2020-05-23 12:21:21');
INSERT INTO `t_ghxx` VALUES ('000016', '002', '001', '001', '14', '0', '6.43', '2020-05-23 12:21:21');
INSERT INTO `t_ghxx` VALUES ('000017', '002', '001', '001', '15', '0', '6.43', '2020-05-23 12:21:22');
INSERT INTO `t_ghxx` VALUES ('000018', '002', '001', '001', '16', '0', '6.43', '2020-05-23 12:21:23');
INSERT INTO `t_ghxx` VALUES ('000019', '002', '001', '001', '17', '0', '6.43', '2020-05-23 12:21:24');
INSERT INTO `t_ghxx` VALUES ('000020', '002', '001', '001', '18', '0', '6.43', '2020-05-23 12:21:25');
INSERT INTO `t_ghxx` VALUES ('000021', '002', '001', '001', '19', '0', '6.43', '2020-05-23 12:21:25');
INSERT INTO `t_ghxx` VALUES ('000022', '002', '001', '001', '20', '0', '6.43', '2020-05-23 12:21:26');
INSERT INTO `t_ghxx` VALUES ('000023', '002', '001', '001', '21', '0', '6.43', '2020-05-23 12:21:28');
INSERT INTO `t_ghxx` VALUES ('000024', '002', '001', '001', '22', '0', '6.43', '2020-05-23 12:21:29');
INSERT INTO `t_ghxx` VALUES ('000025', '002', '001', '001', '23', '0', '6.43', '2020-05-23 12:21:29');

-- ----------------------------
-- Table structure for t_hzxx
-- ----------------------------
DROP TABLE IF EXISTS `t_hzxx`;
CREATE TABLE `t_hzxx` (
  `HZBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `HZMC` char(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `PYZS` char(4) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `KSBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `SFZJ` tinyint(1) NOT NULL,
  `GHRS` int(11) NOT NULL,
  `GHFY` decimal(10,2) NOT NULL,
  PRIMARY KEY (`HZBH`),
  KEY `depid` (`KSBH`),
  CONSTRAINT `t_hzxx_ibfk_1` FOREIGN KEY (`KSBH`) REFERENCES `t_ksxx` (`KSBH`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_hzxx
-- ----------------------------
INSERT INTO `t_hzxx` VALUES ('001', '心血管内科', 'xinx', '01', '1', '23', '24.70');
INSERT INTO `t_hzxx` VALUES ('002', '心血管内科', 'xinx', '01', '0', '23', '6.43');
INSERT INTO `t_hzxx` VALUES ('003', '神经内科', 'shen', '01', '1', '23', '21.29');
INSERT INTO `t_hzxx` VALUES ('004', '神经内科', 'shen', '01', '0', '23', '9.21');
INSERT INTO `t_hzxx` VALUES ('005', '神经外科', 'shen', '02', '1', '17', '58.53');
INSERT INTO `t_hzxx` VALUES ('006', '神经外科', 'shen', '02', '0', '17', '14.20');
INSERT INTO `t_hzxx` VALUES ('007', '胸外科', 'xion', '02', '1', '16', '47.43');
INSERT INTO `t_hzxx` VALUES ('008', '胸外科', 'xion', '02', '0', '16', '10.85');
INSERT INTO `t_hzxx` VALUES ('009', '小儿眼科', 'xiao', '03', '1', '13', '42.22');
INSERT INTO `t_hzxx` VALUES ('010', '眼外伤', 'yanw', '03', '0', '13', '5.19');
INSERT INTO `t_hzxx` VALUES ('011', '眼外伤', 'yanw', '03', '1', '13', '25.29');
INSERT INTO `t_hzxx` VALUES ('012', '角膜科', 'jiao', '03', '0', '13', '14.91');
INSERT INTO `t_hzxx` VALUES ('013', '小儿康复科', 'xiao', '04', '1', '15', '57.61');
INSERT INTO `t_hzxx` VALUES ('014', '小儿康复科', 'xiao', '04', '0', '15', '6.85');
INSERT INTO `t_hzxx` VALUES ('015', '小儿皮肤科', 'xiao', '04', '1', '29', '31.46');
INSERT INTO `t_hzxx` VALUES ('016', '小儿皮肤科', 'xiao', '04', '0', '29', '7.63');
INSERT INTO `t_hzxx` VALUES ('017', '心理咨询', 'xinl', '05', '1', '16', '59.69');
INSERT INTO `t_hzxx` VALUES ('018', '心理咨询', 'xinl', '05', '0', '16', '14.49');
INSERT INTO `t_hzxx` VALUES ('019', '精神障碍科', 'jing', '05', '1', '24', '29.19');
INSERT INTO `t_hzxx` VALUES ('020', '精神障碍科', 'jing', '05', '0', '24', '8.93');
INSERT INTO `t_hzxx` VALUES ('021', '中医内科', 'zhon', '06', '1', '20', '48.18');
INSERT INTO `t_hzxx` VALUES ('022', '中医内科', 'zhon', '06', '0', '20', '7.32');
INSERT INTO `t_hzxx` VALUES ('023', '中医骨伤科', 'zhon', '06', '1', '13', '29.77');
INSERT INTO `t_hzxx` VALUES ('024', '中医骨伤科', 'zhon', '06', '0', '13', '14.56');

-- ----------------------------
-- Table structure for t_ksxx
-- ----------------------------
DROP TABLE IF EXISTS `t_ksxx`;
CREATE TABLE `t_ksxx` (
  `KSBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `KSMC` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `PYZS` char(8) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`KSBH`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_ksxx
-- ----------------------------
INSERT INTO `t_ksxx` VALUES ('01', '内科', 'neike');
INSERT INTO `t_ksxx` VALUES ('02', '外科', 'waike');
INSERT INTO `t_ksxx` VALUES ('03', '眼科', 'yanke');
INSERT INTO `t_ksxx` VALUES ('04', '儿科', 'erke');
INSERT INTO `t_ksxx` VALUES ('05', '精神科', 'jingshen');
INSERT INTO `t_ksxx` VALUES ('06', '中医科', 'zhongyi');

-- ----------------------------
-- Table structure for t_ksys
-- ----------------------------
DROP TABLE IF EXISTS `t_ksys`;
CREATE TABLE `t_ksys` (
  `YSBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `KSBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `YSMC` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `PYZS` char(4) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `DLKL` char(8) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `SFZJ` tinyint(1) NOT NULL,
  `DLRQ` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`YSBH`),
  KEY `depid` (`KSBH`),
  CONSTRAINT `t_ksys_ibfk_1` FOREIGN KEY (`KSBH`) REFERENCES `t_ksxx` (`KSBH`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_ksys
-- ----------------------------
INSERT INTO `t_ksys` VALUES ('001', '01', '刘医生', 'liu', '123456', '0', '2020-05-23 12:05:04');
INSERT INTO `t_ksys` VALUES ('002', '01', '张医生', 'zhan', '123456', '1', '0000-00-00 00:00:00');
INSERT INTO `t_ksys` VALUES ('003', '02', '周医生', 'zhou', '123456', '0', '0000-00-00 00:00:00');
INSERT INTO `t_ksys` VALUES ('004', '02', '胡医生', 'hu', '123456', '1', '2020-05-23 12:05:57');
INSERT INTO `t_ksys` VALUES ('005', '03', '方医生', 'fang', '123456', '0', '0000-00-00 00:00:00');
INSERT INTO `t_ksys` VALUES ('006', '03', '孙医生', 'sun', '123456', '1', '0000-00-00 00:00:00');
INSERT INTO `t_ksys` VALUES ('007', '04', '杜医生', 'du', '123456', '0', '0000-00-00 00:00:00');
INSERT INTO `t_ksys` VALUES ('008', '04', '李医生', 'li', '123456', '1', '0000-00-00 00:00:00');
INSERT INTO `t_ksys` VALUES ('009', '05', '付医生', 'fu', '123456', '0', '0000-00-00 00:00:00');
INSERT INTO `t_ksys` VALUES ('010', '05', '谭医生', 'tan', '123456', '1', '0000-00-00 00:00:00');
INSERT INTO `t_ksys` VALUES ('011', '06', '乔医生', 'qiao', '123456', '0', '0000-00-00 00:00:00');
INSERT INTO `t_ksys` VALUES ('012', '06', '丁医生', 'ding', '123456', '1', '0000-00-00 00:00:00');
