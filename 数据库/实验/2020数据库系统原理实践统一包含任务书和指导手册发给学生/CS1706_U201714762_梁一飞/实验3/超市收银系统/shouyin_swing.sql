/*
 Navicat Premium Data Transfer

 Source Server         : aaa
 Source Server Type    : MySQL
 Source Server Version : 80011
 Source Host           : localhost:3306
 Source Schema         : shouyin_swing

 Target Server Type    : MySQL
 Target Server Version : 80011
 File Encoding         : 65001

 Date: 24/06/2020 00:04:34
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for cashier
-- ----------------------------
DROP TABLE IF EXISTS `cashier`;
CREATE TABLE `cashier`  (
  `cnum` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `cname` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `csex` char(2) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `cuser` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `cpassword` char(16) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`cnum`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of cashier
-- ----------------------------
INSERT INTO `cashier` VALUES ('tangseng', '唐僧', '男', 'ts', '123');
INSERT INTO `cashier` VALUES ('zhubajie', '猪八戒', '男', 'zbj', '123');

-- ----------------------------
-- Table structure for detail
-- ----------------------------
DROP TABLE IF EXISTS `detail`;
CREATE TABLE `detail`  (
  `onum` char(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `gnum` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `quantity` int(10) NULL DEFAULT NULL,
  INDEX `a`(`onum`) USING BTREE,
  INDEX `b`(`gnum`) USING BTREE,
  CONSTRAINT `a` FOREIGN KEY (`onum`) REFERENCES `order` (`onum`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `b` FOREIGN KEY (`gnum`) REFERENCES `goods` (`gnum`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of detail
-- ----------------------------
INSERT INTO `detail` VALUES ('1fd0d2dc9d564b5fbf8799759743ee01', 'bc', 10);
INSERT INTO `detail` VALUES ('f545777be20a4093a840553269c73b27', 'yu', 20);
INSERT INTO `detail` VALUES ('a907e738c8e84ac59238ca824b6c2dc8', 'bc', 1);

-- ----------------------------
-- Table structure for goods
-- ----------------------------
DROP TABLE IF EXISTS `goods`;
CREATE TABLE `goods`  (
  `gnum` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `gname` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `gprice` int(10) NULL DEFAULT NULL,
  `gpoint` int(10) NULL DEFAULT NULL,
  PRIMARY KEY (`gnum`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of goods
-- ----------------------------
INSERT INTO `goods` VALUES ('bc', '白菜', 10, 10);
INSERT INTO `goods` VALUES ('hyk', '会员卡', 50, 1000);
INSERT INTO `goods` VALUES ('qc', '青菜', 5, 5);
INSERT INTO `goods` VALUES ('yu', '鱼', 20, 20);

-- ----------------------------
-- Table structure for member
-- ----------------------------
DROP TABLE IF EXISTS `member`;
CREATE TABLE `member`  (
  `mnum` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `mname` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `msex` char(2) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mpoint` int(10) NULL DEFAULT NULL,
  `mdate` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`mnum`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of member
-- ----------------------------
INSERT INTO `member` VALUES ('swj', '沙悟净', '男', 0, '2020-06-23 23:45:58');
INSERT INTO `member` VALUES ('swk', '孙悟空', '男', 6570, '2020-06-16 01:09:09');

-- ----------------------------
-- Table structure for order
-- ----------------------------
DROP TABLE IF EXISTS `order`;
CREATE TABLE `order`  (
  `onum` char(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mnum` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `cnum` char(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `allprice` double(10, 2) NULL DEFAULT NULL,
  `totalprice` double(10, 2) NULL DEFAULT NULL,
  `odate` datetime(0) NULL DEFAULT NULL,
  INDEX `onum`(`onum`) USING BTREE,
  INDEX `c`(`mnum`) USING BTREE,
  INDEX `d`(`cnum`) USING BTREE,
  CONSTRAINT `c` FOREIGN KEY (`mnum`) REFERENCES `member` (`mnum`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `d` FOREIGN KEY (`cnum`) REFERENCES `cashier` (`cnum`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of order
-- ----------------------------
INSERT INTO `order` VALUES ('1fd0d2dc9d564b5fbf8799759743ee01', 'swj', 'zhubajie', 100.00, 100.00, '2020-06-23 00:00:00');
INSERT INTO `order` VALUES ('f545777be20a4093a840553269c73b27', 'swk', 'zhubajie', 400.00, 360.00, '2020-06-23 00:00:00');
INSERT INTO `order` VALUES ('a907e738c8e84ac59238ca824b6c2dc8', 'swk', 'zhubajie', 10.00, 9.00, '2020-06-24 00:00:00');

SET FOREIGN_KEY_CHECKS = 1;
