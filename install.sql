SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';


-- -----------------------------------------------------
-- Table `language`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `language` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `code` VARCHAR(255) NOT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `user`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `user` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `username` VARCHAR(255) NOT NULL ,
  `password` VARCHAR(255) NOT NULL ,
  `password_salt` VARCHAR(255) NULL ,
  `name` VARCHAR(255) NOT NULL ,
  `address` VARCHAR(255) NOT NULL ,
  `residence` VARCHAR(255) NOT NULL ,
  `email` VARCHAR(255) NULL ,
  `company` VARCHAR(255) NULL ,
  `language_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_user_language1` (`language_id` ASC) ,
  CONSTRAINT `fk_user_language1`
    FOREIGN KEY (`language_id` )
    REFERENCES `language` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `translatable`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `translatable` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `sentence` VARCHAR(255) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `translation`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `translation` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `translation` TEXT NOT NULL ,
  `translatable_id` INT NOT NULL ,
  `language_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_translation_translatable1` (`translatable_id` ASC) ,
  INDEX `fk_translation_language1` (`language_id` ASC) ,
  CONSTRAINT `fk_translation_translatable1`
    FOREIGN KEY (`translatable_id` )
    REFERENCES `translatable` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_translation_language1`
    FOREIGN KEY (`language_id` )
    REFERENCES `language` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `status`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `status` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `translatable_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_status_translatable1` (`translatable_id` ASC) ,
  CONSTRAINT `fk_status_translatable1`
    FOREIGN KEY (`translatable_id` )
    REFERENCES `translatable` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `project`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `project` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(255) NOT NULL ,
  `finished` TINYINT(1) NOT NULL ,
  `status_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_project_status1` (`status_id` ASC) ,
  CONSTRAINT `fk_project_status1`
    FOREIGN KEY (`status_id` )
    REFERENCES `status` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `product`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `product` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(255) NOT NULL ,
  `project_id` INT NOT NULL ,
  `status_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_product_project1` (`project_id` ASC) ,
  INDEX `fk_product_status1` (`status_id` ASC) ,
  CONSTRAINT `fk_product_project1`
    FOREIGN KEY (`project_id` )
    REFERENCES `project` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_product_status1`
    FOREIGN KEY (`status_id` )
    REFERENCES `status` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `document`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `document` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `file_location` VARCHAR(255) NOT NULL ,
  `product_id` INT NOT NULL ,
  `project_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_document_product1` (`product_id` ASC) ,
  INDEX `fk_document_project1` (`project_id` ASC) ,
  CONSTRAINT `fk_document_product1`
    FOREIGN KEY (`product_id` )
    REFERENCES `product` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_document_project1`
    FOREIGN KEY (`project_id` )
    REFERENCES `project` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `invoices`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `invoices` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `file_location` VARCHAR(255) NOT NULL ,
  `project_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_invoices_project1` (`project_id` ASC) ,
  CONSTRAINT `fk_invoices_project1`
    FOREIGN KEY (`project_id` )
    REFERENCES `project` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `right`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `right` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(255) NOT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `user_rights`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `user_rights` (
  `user_id` INT NOT NULL ,
  `right_id` INT NOT NULL ,
  PRIMARY KEY (`user_id`) ,
  INDEX `fk_user_rights_user1` (`user_id` ASC) ,
  INDEX `fk_user_rights_right1` (`right_id` ASC) ,
  CONSTRAINT `fk_user_rights_user1`
    FOREIGN KEY (`user_id` )
    REFERENCES `user` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_user_rights_right1`
    FOREIGN KEY (`right_id` )
    REFERENCES `right` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `document_rights`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `document_rights` (
  `document_id` INT NOT NULL ,
  `right_id` INT NOT NULL ,
  PRIMARY KEY (`document_id`) ,
  INDEX `fk_Documentrechten_document1` (`document_id` ASC) ,
  INDEX `fk_document_rights_right1` (`right_id` ASC) ,
  CONSTRAINT `fk_Documentrechten_document1`
    FOREIGN KEY (`document_id` )
    REFERENCES `document` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_document_rights_right1`
    FOREIGN KEY (`right_id` )
    REFERENCES `right` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `user_has_project`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `user_has_project` (
  `user_id` INT NOT NULL ,
  `project_id` INT NOT NULL ,
  PRIMARY KEY (`user_id`, `project_id`) ,
  INDEX `fk_user_has_project_project1` (`project_id` ASC) ,
  INDEX `fk_user_has_project_user1` (`user_id` ASC) ,
  CONSTRAINT `fk_user_has_project_user1`
    FOREIGN KEY (`user_id` )
    REFERENCES `user` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_user_has_project_project1`
    FOREIGN KEY (`project_id` )
    REFERENCES `project` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `logitems`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `logitems` (
  `project_id` INT NOT NULL ,
  `date` DATETIME NOT NULL ,
  `data` VARCHAR(255) NOT NULL ,
  `translatable_id` INT NOT NULL ,
  PRIMARY KEY (`project_id`) ,
  INDEX `fk_table_log_translatable1` (`translatable_id` ASC) ,
  CONSTRAINT `fk_table_log_project1`
    FOREIGN KEY (`project_id` )
    REFERENCES `project` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_table_log_translatable1`
    FOREIGN KEY (`translatable_id` )
    REFERENCES `translatable` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
