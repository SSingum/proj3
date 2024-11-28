import './App.css';
import 'bootstrap/dist/css/bootstrap.min.css';
import Dropdown from 'react-bootstrap/Dropdown';
import DropdownButton from 'react-bootstrap/DropdownButton';
import logo from './Hash.webp';
import React from 'react';

const labelInput = {
  fontFamily: '"Jersey 10", sans-serif',
  fontSize: "20px",
  color: "#FFFFFF",
  letterSpacing: "3px",
};

function App() {
  return (
    <div className="App">
      <header className="App-header">

        {/*project image*/}
        <img src={logo} className="App-logo" alt="logo" />

        {/*title*/}
        <p>
          Financial Trend Analyzer
        </p>

        {/*dropdown menu info and functionality from https://react-bootstrap.netlify.app/docs/components/dropdowns/*/}
        <DropdownButton id="dropdown-basic-button" title="Select from options below">
          <Dropdown.Item>
            Option 1
          </Dropdown.Item>
          <Dropdown.Item>
            Option 2
          </Dropdown.Item>
          <Dropdown.Item>
            Option 3
          </Dropdown.Item>
        </DropdownButton>

      </header>
    </div>
  );
}

export default App;
